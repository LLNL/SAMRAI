/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and COPYING.LESSER.
 *
 * Copyright:     (c) 1997-2012 Lawrence Livermore National Security, LLC
 * Description:   Abstract base class for spatial coarsening operators.
 *
 ************************************************************************/

#ifndef included_hier_CoarsenOperator_C
#define included_hier_CoarsenOperator_C

#include "SAMRAI/hier/CoarsenOperator.h"

#include "SAMRAI/tbox/StartupShutdownManager.h"

namespace SAMRAI {
namespace hier {

//std::multimap<std::string, CoarsenOperator *> CoarsenOperator::s_lookup_table;
std::shared_ptr<std::multimap<std::string, CoarsenOperator *>> CoarsenOperator::s_lookup_table(new std::multimap<std::string, CoarsenOperator *>);

tbox::StartupShutdownManager::Handler
CoarsenOperator::s_finalize_handler(
   0,
   0,
   0,
   CoarsenOperator::finalizeCallback,
   tbox::StartupShutdownManager::priorityList);

CoarsenOperator::CoarsenOperator(const std::string& name):
   d_name(name)
{
   registerInLookupTable(name);
}

CoarsenOperator::~CoarsenOperator()
{
   //removeFromLookupTable(d_name);
   if(std::shared_ptr<std::multimap<std::string, CoarsenOperator *>> l_lookup_table_lock = l_lookup_table.lock()) {
     removeFromLookupTable(d_name);
   }
}

void
CoarsenOperator::removeFromLookupTable(
   const std::string& name)
{
   /*
    * The lookup table might be empty if static CoarsenOperator's are used
    * in which case the table will have been cleared before the statics
    * are destroyed.
    */
   if (!(*s_lookup_table).empty()) {
      std::multimap<std::string, CoarsenOperator *>::iterator mi =
         (*s_lookup_table).find(name);
      TBOX_ASSERT(mi != (*s_lookup_table).end());
      while (mi->first == name && mi->second != this) {
         ++mi;
         TBOX_ASSERT(mi != (*s_lookup_table).end());
      }
      TBOX_ASSERT(mi->first == name);
      TBOX_ASSERT(mi->second == this);
      mi->second = 0;
      (*s_lookup_table).erase(mi);
   }
}
/*
 *************************************************************************
 * Compute the max coarsen stencil width from all constructed
 * coarsen operators.
 *************************************************************************
 */
IntVector
CoarsenOperator::getMaxCoarsenOpStencilWidth(
   const tbox::Dimension& dim)
{
   IntVector max_width(dim, 0);

   for (std::multimap<std::string, CoarsenOperator *>::const_iterator
        mi = (*s_lookup_table).begin(); mi != (*s_lookup_table).end(); ++mi) {
      const CoarsenOperator* op = mi->second;
      max_width.max(op->getStencilWidth(dim));
   }

   return max_width;
}

}
}
#endif
