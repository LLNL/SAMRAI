/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and LICENSE.
 *
 * Copyright:     (c) 1997-2025 Lawrence Livermore National Security, LLC
 * Description:   Parameters in load balancing.
 *
 ************************************************************************/

#ifndef included_mesh_PartitioningParams
#define included_mesh_PartitioningParams

#include "SAMRAI/SAMRAI_config.h"

#include "SAMRAI/hier/BaseGridGeometry.h"

#include <cmath>
#include <map>

namespace SAMRAI {
namespace mesh {

/*!
 * @brief Light weight class holding parameters generally used
 * in partitioning.
 */

class PartitioningParams
{
public:
   PartitioningParams(
      const hier::BaseGridGeometry& grid_geometry,
      const hier::IntVector& ratio_to_level_zero,
      const hier::IntVector& min_size,
      const hier::IntVector& max_size,
      const hier::IntVector& bad_interval,
      const hier::IntVector& cut_factor,
      size_t minimum_cells,
      double artificial_minimum_load,
      double flexible_load_tol);

   PartitioningParams(
      const PartitioningParams& other);

   double getMinBoxSizeProduct() const {
      return static_cast<double>(d_min_size.getProduct());
   }

   const hier::IntVector& getMinBoxSize() const {
      return d_min_size;
   }

   const hier::IntVector& getMaxBoxSize() const {
      return d_max_size;
   }

   const hier::BoxContainer& getDomainBoxes(const hier::BlockId& bid) const {
      return d_block_domain_boxes.find(bid)->second;
   }

   const hier::IntVector& getBadInterval() const {
      return d_bad_interval;
   }

   const hier::IntVector& getCutFactor() const {
      return d_cut_factor;
   }

   size_t getMinimumCellRequest() const {
      return d_minimum_cells;
   } 

   double getArtificialMinimumLoad() const {
      return d_artificial_minimum_load;
   }

   const tbox::Dimension& getDim() const {
      return d_min_size.getDim();
   }

   const double& getFlexibleLoadTol() const {
      return d_flexible_load_tol;
   }

   const double& getLoadComparisonTol() const {
      return d_load_comparison_tol;
   }

   const bool& usingLinearLoad() const {
      return d_using_linear_load;
   }

   void setUsingLinearLoad(bool using_linear_load) {
      d_using_linear_load = using_linear_load;
   }

   const double& getLoadSlope() const {
      return d_load_slope;
   }

   void setLoadSlope(double load_slope) {
      d_load_slope = load_slope;
   }

   const double& getLoadIntercept() const {
      return d_load_intercept;
   }

   void setLoadIntercept(double load_intercept) {
      d_load_intercept = load_intercept;
   }

   const int& getLoadGhostWidth() const {
      return d_load_ghost_width;
   }

   void setLoadGhostWidth(int load_ghost_width) {
      TBOX_ASSERT(load_ghost_width >= 0);
      d_load_ghost_width = load_ghost_width;
   }

   double computeLinearLoad(double size) const {
       
      if (d_load_ghost_width == 0) {
         return d_load_slope * size + d_load_intercept;
      } else {
         const double dim = static_cast<double>(getDim().getValue());
         TBOX_ASSERT(dim > 0.0);
         const double base_width = std::pow(size, 1.0 / dim);
         const double new_width =
            base_width + 2.0 * static_cast<double>(d_load_ghost_width);
         const double new_size = std::pow(new_width, dim);
         return d_load_slope * new_size + d_load_intercept;
      } 
   }

   double getSizeFromLinearLoad(double load) const {
      TBOX_ASSERT(d_load_slope != 0.0);
      return (load - d_load_intercept) / d_load_slope;
   }

   const bool& usingVouchers() const {
      return d_using_vouchers;
   }

   void setUsingVouchers(bool using_vouchers) {
      d_using_vouchers = using_vouchers;
   }

   const int& getWorkloadDataId() const {
      return d_work_data_id;
   }

   void setWorkloadDataId(int work_data_id) {
      TBOX_ASSERT(work_data_id >= 0);
      d_work_data_id = work_data_id;
   }

   const hier::PatchLevel& getWorkloadPatchLevel() const {
      return *d_workload_level;
   }

   void setWorkloadPatchLevel(std::shared_ptr<hier::PatchLevel>& level) {
      TBOX_ASSERT(level.get());
      d_workload_level = level;
   }


   friend std::ostream&
   operator << (
      std::ostream& os,
      const PartitioningParams& pp);

private:
   std::map<hier::BlockId, hier::BoxContainer> d_block_domain_boxes;
   hier::IntVector d_min_size;
   hier::IntVector d_max_size;
   hier::IntVector d_bad_interval;
   hier::IntVector d_cut_factor;

   /*
    * @brief The requested minimum for number of cells in a patch
    */
   size_t d_minimum_cells;

   /*
    * @brief An optional artificial load value. If used, new boxes smaller
    * than this value are treated as if their load is this value during
    * load balancing operations.
    */
   double d_artificial_minimum_load;

   bool d_using_linear_load;
   double d_load_slope;
   double d_load_intercept; 
   int d_load_ghost_width = 0;

   /*!
    * @brief Fraction of ideal load a process can accept over and
    * above the ideal.
    */
   double d_flexible_load_tol;

   /*!
    * @brief Tolerance for comparing floating point loads.
    *
    * Should be set to at least possible rounding errors.
    * Better if set between that and the greatest work value
    * that would be considered "no work".
    */
   double d_load_comparison_tol;

   /*!
    * @brief Flag for using voucher method or not.
    */
   bool d_using_vouchers;

   /*!
    * @brief Patch data id for nonuniform workload
    */
   int d_work_data_id;

   /*!
    * @brief Pointer to level holding nonuniform workload
    */
   std::shared_ptr<hier::PatchLevel> d_workload_level;
};

}
}

#endif
