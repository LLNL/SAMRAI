# Copyright 2013-2023 Lawrence Livermore National Security, LLC and other
# Spack Project Developers. See the top-level COPYRIGHT file for details.
#
# SPDX-License-Identifier: (Apache-2.0 OR MIT)

from spack.build_systems.autotools import AutotoolsBuilder
from spack.build_systems.cmake import CMakeBuilder
from spack.package import *

class Samrai(CMakePackage, AutotoolsPackage, CudaPackage):
  """SAMRAI (Structured Adaptive Mesh Refinement Application Infrastructure)
    is an object-oriented C++ software library enables exploration of
    numerical, algorithmic, parallel computing, and software issues
    associated with applying structured adaptive mesh refinement
    (SAMR) technology in large-scale parallel application development.
    """

  homepage = "https://computing.llnl.gov/projects/samrai"
  git = "https://github.com/LLNL/samrai.git"
  tags = ["radiuss"]
  maintainers = ["gunney1"]

  def url_for_version(self, version):
    if version.up_to(1) >= Version(4):
      dirUrl = f'https://github.com/LLNL/SAMRAI/releases/download'
    else:
      dirUrl = f'https://computing.llnl.gov/projects/samrai/download'
    url = dirUrl + f'/SAMRAI-v{version.dotted}.tar.gz'
    return url

  version("develop", branch="develop")
  version("4.2.0", sha256="34a256c99e29bee6dee017253a18cf1ed6435f0376e666e235e9092a895fabc6")
  version("4.1.2", sha256="2860c693ba495613ce0ea04cc72eb8749519a770d520ef0a83a54ecff3d515e3")
  version("4.1.1", sha256="ceb6e5b3b1587c45b8c41971f252974e40eae3d5fe9ad93269d969ea4acc2637")
  version("4.1.0", sha256="633968bf1d4ff9c0f1f0c31591f9bb665f8252231a9ca03b54c3b498239a5815")
  version("3.12.0", sha256="b8334aa22330a7c858e09e000dfc62abbfa3c449212b4993ec3c4035bed6b832")
  version("3.11.2", sha256="fd9518cc9fd8c8f6cdd681484c6eb42114aebf2a6ba4c8e1f12b34a148dfdefb")
  version("3.11.1", sha256="14317938e55cb7dc3eca21d9b7667a256a08661c6da988334f7af566a015b327")
  version("3.11.0", sha256="4033f9fd02e09990bd564d226d84df5bae6baa16e51ab29e8a607a6d593a3806")
  version("3.10.0", sha256="59eeeb2d3b7e52ea45efb037272e36666940682407ae159dab9066aad527cfa0")
  version("3.9.0", sha256="1ffdbdf454986fdfd8a599f4b0a14c17e2e9563fe6041d91203c88c5174fd117")
  version("3.8.1", sha256="963e6d6faec52cdb86a14f7b8564f6641fc2241e004ca54405f6bc5f7b593066")

  build_system(
    conditional("cmake", when="@3.13:"),
    conditional("autotools", when="@:3.12"),
    default="cmake",
  )

  # debug variant is only for autotools build.
  # With CMake, use build_type=Debug, provided by CMakePackage.
  variant("debug", default=False, when='build_system=autotools',
          description="Configure with debug options.")

  variant("shared", default=False, description="Build shared libraries")

  # After some version (I'm guessing 4), we support conduit.
  # TODO: verify and correct.
  variant("conduit", default=False, when='@4:',
          description="Enable support for conduit")

  variant('boost', default=False, description='Enable support for boost', when='@3.0:3.11')
  variant("cuda", default=False, description="Enable support for cuda")
  variant("hdf5", default=True, description="Enable support for hdf5")
  variant("hip", default=False, description="Enable support for hip")
  variant("hypre", default=False, description="Enable support for hypre")
  variant("mpi", default=True, description="Enable support for MPI")
  variant("openmp", default=False, description="Enable support for OPENMP")
  variant("petsc", default=False, description="Enable support for petsc")
  variant("raja", default=False, description="Enable support for raja")
  variant("silo", default=False, description="Enable support for silo")
  variant("sundials", default=False, description="Enable support for sundials")
  variant("umpire", default=False, description="Enable support for umpire")

  # Couldn't find zlib in SAMRAI cmake builds.
  # Assuming it's only in autotools build.
  depends_on("zlib", when='build_system=autotools')

  depends_on('boost', when='+boost')

  depends_on("mpi", when="+mpi")

  # Bring in dependencies for variants that don't use MPI.
  for tpl in 'raja cuda hip umpire'.split():
    with when(f'+{tpl}'):
      depends_on(tpl)

  # Pass mpi variants to dependency packages that use them.
  for tpl in 'hdf5 hypre petsc sundials silo'.split():
    with when(f'+{tpl}'):
      depends_on(f"{tpl}+mpi", when="+mpi")
      depends_on(f"{tpl}~mpi", when="~mpi")

  with when("+conduit"):
    # If ~mpi, use a non-parmetis conduit, because parmetis requires mpi.
    depends_on("conduit+mpi+parmetis", when="+mpi")
    depends_on("conduit~mpi~parmetis", when="~mpi")


class CMakeBuilder(spack.build_systems.cmake.CMakeBuilder):
  def cmake_args(self):
    options = []

    sharedLibMode = 'ON' if '+shared' in self.spec else 'OFF'
    options.append('-DBUILD_SHARED_LIBS=' + sharedLibMode)

    # Third-party libs handled with either
    # ENABLE_TPL=OFF or TPL_DIR=/path/to/tpl/install.
    for tpl in 'conduit cuda hdf5 hypre raja petsc silo sundials'.split():
      TPL = tpl.upper()
      if f'~{tpl}' in self.spec:
        options.append(f'-DENABLE_{TPL}=OFF')
      else:
        options.append(f'-D{TPL}_DIR=' + self.spec[tpl].prefix)

    # Umpire has unconventional capitalization in cmake command.
    if '~umpire' in self.spec:
      options.append(f'-DENABLE_UMPIRE=OFF')
    else:
      options.append(f'-Dumpire_DIR=' + self.spec['umpire'].prefix)

    # Third-party libs handled with either
    # ENABLE_TPL=OFF or ENABLE_TPL=ON
    for tpl in 'openmp'.split():
      tplMode = 'ON' if f'+{tpl}' in self.spec else 'OFF'
      TPL = tpl.upper()
      options.append(f'-DENABLE_{TPL}={tplMode}')

    return options


class AutotoolsBuilder(spack.build_systems.autotools.AutotoolsBuilder):
  def configure_args(self):
    options = []

    # SAMRAI 2 used templates; enable implicit instantiation
    if self.spec.satisfies("@:2"):
      options.append("--enable-implicit-template-instantiation")

    if "+shared" in self.spec:
      options.append("--enable-shared")
    else:
      options.append("--disable-shared")

    if "+debug" in self.spec:
      options.extend('--disable-opt --enable-debug'.split())
    else:
      options.extend('--enable-opt --disable-debug'.split())

    # Third-parth libs specified as either
    # --with-tpl=/path/to/tpl/install or --without-tpl
    for tpl in 'boost hdf5 hypre petsc silo sundials'.split():
      if f'+{tpl}' in self.spec:
        options.append(f'--with-{tpl}=' + self.spec[tpl].prefix)
      else:
        options.append(f'--without-{tpl}')

    options.extend('--without-blas --without-lapack'.split())

    if '+zlib' in self.spec:
      options.append(f'--with-zlib={self.spec["zlib"].prefix}')

    return options
