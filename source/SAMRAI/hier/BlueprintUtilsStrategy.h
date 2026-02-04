/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and LICENSE.
 *
 * Copyright:     (c) 1997-2026 Lawrence Livermore National Security, LLC
 * Description:   BlueprintUtilsStrategy
 *
 ************************************************************************/
#ifndef included_hier_BlueprintUtilsStrategy
#define included_hier_BlueprintUtilsStrategy

#include "SAMRAI/SAMRAI_config.h"

#include "SAMRAI/hier/Patch.h"
#include "SAMRAI/tbox/Database.h"

#include <memory>

namespace SAMRAI {
namespace hier {

/*!
 * @brief Strategy class for use by BlueprintUtils
 *
 * This abstract base class can be used by BlueprintUtils for call-backs
 * to application code.
 *
 * @see BlueprintUtils 
 */
class BlueprintUtilsStrategy
{

public:

   /*!
    * @brief Constructor
    */
   BlueprintUtilsStrategy();

   /*!
    * @brief Destructor
    */
   virtual ~BlueprintUtilsStrategy();

   /*!
    * @brief Put blueprint coordinate information into a database
    *
    * This pure virtual function provides an interface to call into application
    * code to put coordinate information into a database that is part of
    * a blueprint description of the mesh.  The coordinates for a single patch
    * should be put into the database, using one of blueprint's recognized
    * coordinate types:  uniform, rectilinear, or explicit.
    *
    * @param coords_db   Database to hold coordinate information
    * @param patch       Patch for which coordinates will be described
    * @param box         Coordinate information should be described for
    *                    intersection of this box and the patch's box
    */
   virtual void putCoordinatesToDatabase(
      std::shared_ptr<tbox::Database>& coords_db,
      const Patch& patch,
      const Box& box) = 0;

private:


};

}
}

#endif  // included_hier_BlueprintUtils
