#include "Stencil.h"

#include "SAMRAI/hier/ForAll.h"
#include "SAMRAI/pdat/CellData.h"
#include "SAMRAI/tbox/Collectives.h"

#include "SAMRAI/geom/CartesianPatchGeometry.h"
#include "SAMRAI/appu/CartesianBoundaryDefines.h"

#include "SAMRAI/tbox/NVTXUtilities.h"

#include "math.h"

#define MAX(a, b) fmax(a, b)
#define MIN(a, b) fmin(a, b)
#define ABS(a) fabs(a)

Stencil::Stencil(
   const std::string& name,
   const tbox::Dimension& dim,
   std::shared_ptr<tbox::Database> input_db,
   std::shared_ptr<geom::CartesianGridGeometry> grid_geom):
   algs::HyperbolicPatchStrategy(),
   d_object_name(name),
   d_grid_geometry(grid_geom),
   d_velocity({1.0,0.0,0.0}),
   d_dim(dim),
   d_allocator(tbox::AllocatorDatabase::getDatabase()->getDefaultAllocator()),
   d_rho_variables(),
   d_rho_update(),
   d_nghosts(hier::IntVector(dim, 2))
{
   SAMRAI_CALI_CXX_MARK_FUNCTION;
   const int num_variables = input_db->getIntegerWithDefault("num_variables", 1);

   d_tag_threshold = input_db->getDoubleWithDefault("tag_threshold", 0.5);

   d_rho_update = std::make_shared<pdat::CellVariable<double> >(dim, "update", d_allocator, 1);

   for (int i = 0; i < num_variables; ++i) {
      std::ostringstream oss;
      oss << "rho_" << i;
      std::string var_name = oss.str();

      d_rho_variables.push_back( std::make_shared<pdat::CellVariable<double> >(dim, var_name, d_allocator, 1));
   }

}

void
Stencil::registerModelVariables(
   algs::HyperbolicLevelIntegrator* integrator)
{
   integrator->registerVariable(
      d_rho_update,
      hier::IntVector::getZero(d_dim),
      algs::HyperbolicLevelIntegrator::TEMPORARY,
      d_grid_geometry);

   int i = 0;
   for ( const auto& rho_var : d_rho_variables ) {

      integrator->registerVariable(
         rho_var,
         d_nghosts,
         algs::HyperbolicLevelIntegrator::TIME_DEP,
         d_grid_geometry,
         "CONSERVATIVE_COARSEN",
         "CONSERVATIVE_LINEAR_REFINE");

#ifdef HAVE_HDF5
      if (i == 0) {
         hier::VariableDatabase* vardb = hier::VariableDatabase::getDatabase();

         d_visit_writer->registerPlotQuantity(
            rho_var->getName(),
            "SCALAR",
            vardb->mapVariableAndContextToIndex(
               rho_var, integrator->getPlotContext()));
      }
#endif
      i++;
   }
}

void
Stencil::initializeDataOnPatch(
   hier::Patch& patch,
   const double data_time,
   const bool initial_time)
{
   SAMRAI_CALI_CXX_MARK_FUNCTION;
   RANGE_PUSH("Stencil::init", 1);
   NULL_USE(data_time);
   NULL_USE(initial_time);
   // initialize
   if (initial_time) {
      if (d_dim.getValue() == 2) {
        for ( const auto& rho_var : d_rho_variables ) {
           auto rho = pdat::get_view<2, pdat::CellData<double> >(patch.getPatchData(rho_var, getDataContext()));

           hier::parallel_for_all(patch.getBox(), [=] SAMRAI_HOST_DEVICE (int j, int k) {
              rho(j,k) = 0.0;
           });
        }
      } else {
        for ( const auto& rho_var : d_rho_variables ) {
           auto rho = pdat::get_view<3, pdat::CellData<double> >(patch.getPatchData(rho_var, getDataContext()));

           hier::parallel_for_all(patch.getBox(), [=] SAMRAI_HOST_DEVICE (int i, int j, int k) {
              rho(i,j,k) = 0.0;
           });

        }
      }
   }

   RANGE_POP;
}

double
Stencil::computeStableDtOnPatch(
   hier::Patch& patch,
   const bool initial_time,
   const double dt_time)
{
   SAMRAI_CALI_CXX_MARK_FUNCTION;
   RANGE_PUSH("Stencil::dt", 1);
   NULL_USE(initial_time);
   NULL_USE(dt_time);
   const std::shared_ptr<geom::CartesianPatchGeometry> pgeom(
      SAMRAI_SHARED_PTR_CAST<geom::CartesianPatchGeometry>(patch.getPatchGeometry()));
   double dx = pgeom->getDx()[0];
   double dy = pgeom->getDx()[1];
   double min_length = dx > dy ? dy : dx;
   if (d_dim.getValue() == 3) {
      double dz = pgeom->getDx()[2];
      min_length = min_length > dz ? dz : min_length;
   }

   double velocity_mag = std::sqrt(d_velocity[0]*d_velocity[0] + d_velocity[1]*d_velocity[1] + d_velocity[2]*d_velocity[2]);

   RANGE_POP;

   return min_length / velocity_mag;
}

void
Stencil::computeFluxesOnPatch(
   hier::Patch& patch,
   const double time,
   const double dt)
{
   NULL_USE(patch);
   NULL_USE(time);
   NULL_USE(dt);
}

void
Stencil::conservativeDifferenceOnPatch(
   hier::Patch& patch,
   const double time,
   const double dt,
   bool at_syncronization)
{
   SAMRAI_CALI_CXX_MARK_FUNCTION;
   RANGE_PUSH("Stencil::conservativeDifference", 1);
   NULL_USE(time);
   NULL_USE(at_syncronization);

   const std::shared_ptr<geom::CartesianPatchGeometry> pgeom(
      SAMRAI_SHARED_PTR_CAST<geom::CartesianPatchGeometry>(patch.getPatchGeometry()));

   if (d_dim.getValue() == 2) {
      auto rho_new = pdat::get_view<2, pdat::CellData<double>>(patch.getPatchData(d_rho_update, getDataContext()));

      const double dx = pgeom->getDx()[0];
      const double dy = pgeom->getDx()[1];
      for ( const auto& rho_var : d_rho_variables ) {
         auto rho = pdat::get_view<2, pdat::CellData<double>>(patch.getPatchData(rho_var, getDataContext()));

         const double an_abs_lr = ABS(d_velocity[0]) * 0.5;
         const double an_abs_tb = ABS(d_velocity[1]) * 0.5;
         const double an_lr = d_velocity[0] * 0.5;
         const double an_tb = d_velocity[1] * 0.5;

         hier::parallel_for_all(patch.getBox(), [=] SAMRAI_HOST_DEVICE (int j, int k) {
            const double FL = (rho(j-1,k) + rho(j,k)) * an_abs_lr + (rho(j-1,k) - rho(j,k)) * an_lr;
            const double FR = (rho(j,k) + rho(j+1,k)) * an_abs_lr + (rho(j,k) - rho(j+1,k)) * an_lr;
            const double FT = (rho(j,k) + rho(j,k+1)) * an_abs_tb + (rho(j,k) - rho(j,k+1)) * an_tb;
            const double FB = (rho(j,k-1) + rho(j,k)) * an_abs_tb + (rho(j,k-1) - rho(j,k)) * an_tb;
            rho_new(j,k) = rho(j,k) - dt * (1.0 / dx * (FR - FL) + 1.0 / dy * (FT - FB));
         });

         hier::parallel_for_all(patch.getBox(), [=] SAMRAI_HOST_DEVICE (int j, int k) {
            rho(j,k) = rho_new(j,k);
         });
      }
   } else {
      auto rho_new = pdat::get_view<3, pdat::CellData<double>>(patch.getPatchData(d_rho_update, getDataContext()));

      const double dx = pgeom->getDx()[0];
      const double dy = pgeom->getDx()[1];
      const double dz = pgeom->getDx()[2];
      for ( const auto& rho_var : d_rho_variables ) {
         auto rho = pdat::get_view<3, pdat::CellData<double>>(patch.getPatchData(rho_var, getDataContext()));

         const double an_abs_I = ABS(d_velocity[0]) * 0.5;
         const double an_abs_J = ABS(d_velocity[1]) * 0.5;
         const double an_abs_K = ABS(d_velocity[2]) * 0.5;
         const double an_I = d_velocity[0] * 0.5;
         const double an_J = d_velocity[1] * 0.5;
         const double an_K = d_velocity[2] * 0.5;

         hier::parallel_for_all(patch.getBox(), [=] SAMRAI_HOST_DEVICE (int i, int j, int k) {
            const double IL = (rho(i-1,j,k) + rho(i,j,k)) * an_abs_I + (rho(i-1,j,k) - rho(i,j,k)) * an_I;
            const double IH = (rho(i,j,k) + rho(i+1,j,k)) * an_abs_I + (rho(i,j,k) - rho(i+1,j,k)) * an_I;
            const double JL = (rho(i,j,k) + rho(i,j-1,k)) * an_abs_J + (rho(i,j,k) - rho(i,j-1,k)) * an_J;
            const double JH = (rho(i,j+1,k) + rho(i,j,k)) * an_abs_J + (rho(i,j+1,k) - rho(i,j,k)) * an_J;
            const double KL = (rho(i,j,k) + rho(i,j,k-1)) * an_abs_K + (rho(i,j,k) - rho(i,j,k-1)) * an_K;
            const double KH = (rho(i,j,k+1) + rho(i,j,k)) * an_abs_K + (rho(i,j,k+1) - rho(i,j,k)) * an_K;
            rho_new(i,j,k) = rho(i,j,k) - dt * (1.0 / dx * (IH - IL) + 1.0 / dy * (JH - JL) + 1.0 / dz * (KH - KL));
         });

         hier::parallel_for_all(patch.getBox(), [=] SAMRAI_HOST_DEVICE (int i, int j, int k) {
            rho(i,j,k) = rho_new(i,j,k);
         });

      }
   }
   RANGE_POP;
}

void
Stencil::tagGradientDetectorCells(
   hier::Patch& patch,
   const double regrid_time,
   const bool initial_error,
   const int tag_index,
   const bool uses_richardson_extrapolation_too)
{
   SAMRAI_CALI_CXX_MARK_FUNCTION;
   RANGE_PUSH("Stencil::tag", 1);
   NULL_USE(regrid_time);
   NULL_USE(initial_error);
   NULL_USE(uses_richardson_extrapolation_too);
   /*
    * Only need to tag the first variable.
    */

   double tag_threshold = d_tag_threshold;

   if (d_dim.getValue() == 2) {
      auto rho = pdat::get_const_view<2, pdat::CellData<double> >(patch.getPatchData(d_rho_variables[0], getDataContext()));

      auto tags = pdat::get_view<2, pdat::CellData<int> >(patch.getPatchData(tag_index));


      hier::parallel_for_all(patch.getBox(), [=] SAMRAI_HOST_DEVICE (int j, int k) {
         const double d2x = ABS(rho(j+1,k) - 2.0*rho(j,k) + rho(j-1,k));
         const double d2y = ABS(rho(j,k+1) - 2.0*rho(j,k) + rho(j,k-1));

         /*
          * TODO: fix boundary conditions for diagonal gradient detection
          */
         const double dxy = 0.0; // ABS(rho(j+1,k+1) - 2.0*rho(j,k) + rho(j-1,k-1));
         const double dyx = 0.0; // ABS(rho(j-1,k+1) - 2.0*rho(j,k) + rho(j+1,k-1));

         const double dd = MAX(d2x,MAX(d2y,MAX(dxy,dyx)));

         if (dd > tag_threshold) {
            tags(j,k) = 1;
         }
      });
   } else {
      auto rho = pdat::get_const_view<3, pdat::CellData<double> >(patch.getPatchData(d_rho_variables[0], getDataContext()));

      auto tags = pdat::get_view<3, pdat::CellData<int> >(patch.getPatchData(tag_index));


      hier::parallel_for_all(patch.getBox(), [=] SAMRAI_HOST_DEVICE (int i, int j, int k) {
         const double d2x = ABS(rho(i+1,j,k) - 2.0*rho(i,j,k) + rho(i-1,j,k));
         const double d2y = ABS(rho(i,j+1,k) - 2.0*rho(i,j,k) + rho(i,j-1,k));
         const double d2z = ABS(rho(i,j,k+1) - 2.0*rho(i,j,k) + rho(i,j,k-1));

         /*
          * TODO: fix boundary conditions for diagonal gradient detection
          */

         const double dd = MAX(d2x,MAX(d2y,d2z));

         if (dd > tag_threshold) {
            tags(i,j,k) = 1;
         }
      });
   }

   RANGE_POP;
}

void
Stencil::setPhysicalBoundaryConditions(
   hier::Patch& patch,
   const double fill_time,
   const hier::IntVector& ghost_width_to_fill)
{
   SAMRAI_CALI_CXX_MARK_FUNCTION;
   RANGE_PUSH("Stencil::boundaries", 1);
   NULL_USE(fill_time);
  
   const int depth = ghost_width_to_fill[0];

   const std::shared_ptr<geom::CartesianPatchGeometry> pgeom(
      SAMRAI_SHARED_PTR_CAST<geom::CartesianPatchGeometry>(patch.getPatchGeometry()));

   if (d_dim.getValue() == 2) {
      const std::vector<hier::BoundaryBox>& edge_bdry
         = pgeom->getCodimensionBoundaries(Bdry::EDGE2D);


      for ( const auto& rho_var : d_rho_variables ) {
         auto field = pdat::get_view<2, pdat::CellData<double> >(patch.getPatchData(rho_var, getDataContext()));

         const hier::Index ifirst = patch.getBox().lower();
         const hier::Index ilast = patch.getBox().upper();

         const int ifirst0 = ifirst(0);
         const int ifirst1 = ifirst(1);
         const int ilast0 = ilast(0);
         const int ilast1 = ilast(1);

         for(unsigned int i = 0; i < edge_bdry.size(); i++) {

            const auto edge = edge_bdry[i].getLocationIndex();

            const hier::Box boundary_box(pgeom->getBoundaryFillBox(
                                            edge_bdry[i],
                                            patch.getBox(),
                                            ghost_width_to_fill));

            switch(edge) {
            case (BdryLoc::YLO) :
            {
               hier::parallel_for_all(boundary_box, 0, [=] SAMRAI_HOST_DEVICE (int j) {
                  field(j, ifirst1-1)  = field(j,ifirst1);
                  if (depth == 2) { field(j, ifirst1-2)  = field(j,ifirst1+1); }
               });
            }
            break;
            case (BdryLoc::YHI) :
            {
               hier::parallel_for_all(boundary_box, 0, [=] SAMRAI_HOST_DEVICE (int j) {
                  field(j,ilast1+1) = field(j,ilast1);
                  if (depth == 2) { field(j,ilast1+2) = field(j,ilast1-1); }
               });
            }
            break;
            case (BdryLoc::XLO) :
            {
               hier::parallel_for_all(boundary_box, 1, [=] SAMRAI_HOST_DEVICE (int k) {
                  field(ifirst0-1,k) = 1.0;
                  if (depth == 2) { field(ifirst0-2,k) = 1.0; }
               });
            }
            break;
            case (BdryLoc::XHI) :
            {
               hier::parallel_for_all(boundary_box, 1, [=] SAMRAI_HOST_DEVICE (int k) {
                  field(ilast0+1,k) = field(ilast0,k);
                  if (depth == 2) { field(ilast0+2,k) = field(ilast0-1,k); }
               });
            }
            break;
            }
         }
      } // for rho_var
   } else {

      const std::vector<hier::BoundaryBox>& face_bdry
         = pgeom->getCodimensionBoundaries(Bdry::FACE3D);


      for ( const auto& rho_var : d_rho_variables ) {
         auto field = pdat::get_view<3, pdat::CellData<double> >(patch.getPatchData(rho_var, getDataContext()));

         const hier::Index ifirst = patch.getBox().lower();
         const hier::Index ilast = patch.getBox().upper();

         const int ifirst0 = ifirst(0);
         const int ifirst1 = ifirst(1);
         const int ifirst2 = ifirst(2);
         const int ilast0 = ilast(0);
         const int ilast1 = ilast(1);
         const int ilast2 = ilast(2);

         for(unsigned int b = 0; b < face_bdry.size(); b++) {

            const auto face = face_bdry[b].getLocationIndex();

            const hier::Box& boundary_box = face_bdry[b].getBox();

            switch(face) {
            case (BdryLoc::ZLO) :
            {
               hier::parallel_for_all(boundary_box, [=] SAMRAI_HOST_DEVICE (int i, int j, int k) {
                  field(i,j,ifirst2-1)  = field(i,j,ifirst2);
                  field(i,j,ifirst2-2)  = field(i,j,ifirst2+1);
               });
            }
            break;
            case (BdryLoc::ZHI) :
            {
               hier::parallel_for_all(boundary_box, [=] SAMRAI_HOST_DEVICE (int i, int j, int k) {
                  field(i,j,ilast2+1) = field(i,j,ilast2);
                  field(i,j,ilast2+2) = field(i,j,ilast2-1);
               });
            }
            break;
            case (BdryLoc::YLO) :
            {
               hier::parallel_for_all(boundary_box, [=] SAMRAI_HOST_DEVICE (int i, int j, int k) {
                  field(i,ifirst1-1,k)  = field(i,ifirst1,k);
                  field(i,ifirst1-2,k)  = field(i,ifirst1+1,k);
               });
            }
            break;
            case (BdryLoc::YHI) :
            {
               hier::parallel_for_all(boundary_box, [=] SAMRAI_HOST_DEVICE (int i, int j, int k) {
                  field(i,ilast1+1,k) = field(i,ilast1,k);
                  field(i,ilast1+2,k) = field(i,ilast1-1,k);
               });
            }
            break;
            case (BdryLoc::XLO) :
            {
               hier::parallel_for_all(boundary_box, [=] SAMRAI_HOST_DEVICE (int i, int j, int k) {
                  field(ifirst0-1,j,k) = 1.0;
                  field(ifirst0-2,j,k) = 1.0;
               });
            }
            break;
            case (BdryLoc::XHI) :
            {
               hier::parallel_for_all(boundary_box, [=] SAMRAI_HOST_DEVICE (int i, int j, int k) {
                  field(ilast0+1,j,k) = field(ilast0,j,k);
                  field(ilast0+2,j,k) = field(ilast0-1,j,k);
               });
            }
            break;
            }
         }
      } // for rho_var
   }

   RANGE_POP;
}

double
Stencil::computeNorm(const std::shared_ptr<hier::VariableContext>& context, hier::Patch& patch) const
{
   const std::shared_ptr<geom::CartesianPatchGeometry> pgeom(
      SAMRAI_SHARED_PTR_CAST<geom::CartesianPatchGeometry>(patch.getPatchGeometry()));

   double dx = pgeom->getDx()[0];
   double dy = pgeom->getDx()[1];
   double dz = 0.0;
   if (d_dim.getValue() == 3) {
      dz = pgeom->getDx()[2];
   }

   tbox::parallel_reduction_variable_t<tbox::Reduction::Sum, double> norm(0.0);

   if (d_dim.getValue() == 2) { 
      for ( const auto& rho_var : d_rho_variables ) {
         auto rho = pdat::get_const_view<2, pdat::CellData<double>>(patch.getPatchData(rho_var, context));
         hier::parallel_for_all(patch.getBox(), [=] SAMRAI_HOST_DEVICE (int j, int k) {
            norm += ABS(rho(j,k)) * dx * dy;
         });
      }
   } else {
      for ( const auto& rho_var : d_rho_variables ) {
         auto rho = pdat::get_const_view<3, pdat::CellData<double>>(patch.getPatchData(rho_var, context));

         hier::parallel_for_all(patch.getBox(), [=] SAMRAI_HOST_DEVICE (int i, int j, int k) {
            norm += ABS(rho(i,j,k)) * dx * dy * dz;
         });

      }
   }
   return norm.get();
}

void
Stencil::postprocessRefine(
   hier::Patch& fine,
   const hier::Patch& coarse,
   const hier::Box& fine_box,
   const hier::IntVector& ratio)
{
   NULL_USE(fine);
   NULL_USE(coarse);
   NULL_USE(fine_box);
   NULL_USE(ratio);
   setNeedRefineSynchronize(false);
}

void
Stencil::postprocessRefineLevel(
   hier::PatchLevel& fine_level,
   const hier::PatchLevel& coarse_level,
   const hier::Connector& coarse_to_fine,
   const hier::Connector& coarse_to_unfilled)
{
   NULL_USE(fine_level);
   NULL_USE(coarse_level);
   NULL_USE(coarse_to_fine);
   NULL_USE(coarse_to_unfilled);
   setNeedRefineSynchronize(true);
}

void
Stencil::postprocessCoarsen(
   hier::Patch& coarse,
   const hier::Patch& fine,
   const hier::Box& coarse_box,
   const hier::IntVector& ratio)
{
   NULL_USE(coarse); 
   NULL_USE(fine); 
   NULL_USE(coarse_box); 
   NULL_USE(ratio); 
   setNeedCoarsenSynchronize(false);
}

void
Stencil::postprocessCoarsenLevel(
   hier::PatchLevel& coarse_level,
   const hier::PatchLevel& fine_level) {
   NULL_USE(coarse_level);
   NULL_USE(fine_level);
   setNeedCoarsenSynchronize(true);
}


void
Stencil::readDirichletBoundaryDataEntry(
   const std::shared_ptr<tbox::Database>& db,
   std::string& db_name,
   int bdry_location_index)
{
   NULL_USE(db);
   NULL_USE(db_name);
   NULL_USE(bdry_location_index);
   // no-op
}

void
Stencil::readNeumannBoundaryDataEntry(
   const std::shared_ptr<tbox::Database>& db,
   std::string& db_name,
   int bdry_location_index)
{
   NULL_USE(db);
   NULL_USE(db_name);
   NULL_USE(bdry_location_index);
   // no-op
}

#ifdef HAVE_HDF5
void
Stencil::registerVisItDataWriter(std::shared_ptr<appu::VisItDataWriter> viz_writer)
{
   d_visit_writer = viz_writer;
}
#endif
