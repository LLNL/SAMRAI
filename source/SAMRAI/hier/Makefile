#########################################################################
##
## This file is part of the SAMRAI distribution.  For full copyright 
## information, see COPYRIGHT and LICENSE. 
##
## Copyright:     (c) 1997-2018 Lawrence Livermore National Security, LLC
## Description:   primary makefile for compiling the SAMRAI hier package 
##
#########################################################################


SAMRAI        = ../../..
SRCDIR        = .
SUBDIR        = source/SAMRAI/hier

OBJECT        = ../../..

default: library

include $(OBJECT)/config/Makefile.config

SUBDIRS = fortran

OBJS = 	\
	BaseGridGeometry.o \
	BlockId.o \
	BoxContainer.o \
	CoarseFineBoundary.o \
	LocalId.o \
	PatchBoundaries.o \
	PatchHierarchy.o \
	HierarchyNeighbors.o \
	FlattenedHierarchy.o \
	PatchLevel.o \
	PatchLevelFactory.o \
	PeriodicId.o \
	SingularityFinder.o \
	PatchDataRestartManager.o \
	VariableDatabase.o \
	Variable.o \
	PatchDescriptor.o \
	PatchFactory.o \
	PatchDataFactory.o \
	Patch.o \
	PatchGeometry.o \
	PatchData.o \
	BoxLevelConnectorUtils.o \
	BoxContainerUtils.o \
	BaseConnectorAlgorithm.o \
	OverlapConnectorAlgorithm.o \
	MappingConnectorAlgorithm.o \
	Connector.o \
	MappingConnector.o \
	ConnectorStatistics.o \
	BoxLevelHandle.o \
	PeriodicShiftCatalog.o \
	RealBoxConstIterator.o \
	BoxContainerSingleBlockIterator.o \
	BoxContainerSingleOwnerIterator.o \
	BoxTree.o \
	MultiblockBoxTree.o \
	AssumedPartitionBox.o \
	AssumedPartition.o \
	BoxLevel.o \
	BoxLevelStatistics.o \
	PersistentOverlapConnectors.o \
	BoxNeighborhoodCollection.o \
	BoxOverlap.o \
	BoxGeometry.o \
	BoundaryBoxUtils.o \
	BoxUtilities.o \
	BoundaryBox.o \
	BoundaryLookupTable.o \
	Box.o \
	Index.o \
	IntVector.o \
	GlobalId.o \
	BoxId.o \
	ProcessorMapping.o \
	ComponentSelector.o \
	VariableContext.o \
	TransferOperatorRegistry.o \
	CoarsenOperator.o \
	RefineOperator.o \
	TimeInterpolateOperator.o \
	Transformation.o \
	UncoveredBoxIterator.o

library: $(OBJS)
	for DIR in $(SUBDIRS); do if test -d $$DIR; then (cd $$DIR && $(MAKE) $@) ; fi || exit 1; done
clean:
	$(CLEAN_COMMON_LIB_FILES)
	for DIR in $(SUBDIRS); do if test -d $$DIR; then (cd $$DIR && $(MAKE) $@) ; fi || exit 1; done

include $(SRCDIR)/Makefile.depend
