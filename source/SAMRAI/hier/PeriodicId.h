/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and LICENSE.
 *
 * Copyright:     (c) 1997-2024 Lawrence Livermore National Security, LLC
 * Description:   Periodic shift identifier in periodic domain.
 *
 ************************************************************************/

#ifndef included_hier_PeriodicId
#define included_hier_PeriodicId

#include "SAMRAI/SAMRAI_config.h"

#include <iostream>

namespace SAMRAI {
namespace hier {

/*!
 * @brief Generic identifier for identifying the periodic shift.
 *
 * Comparison operators are provided to define sorted ordering of
 * objects.
 */
class PeriodicId
{

public:
   /*!
    * @brief Default constructor.
    */
   constexpr PeriodicId() :
      d_value(s_invalid_val)
   {
   }

   /*!
    * @brief Copy constructor.
    */
   constexpr PeriodicId(
      const PeriodicId& other) = default;

   /*!
    * @brief Construct from a numerical value.
    *
    * This method is explicit to prevent automatic conversion.
    */
   constexpr explicit PeriodicId(
      const int& value) :
      d_value(value)
   {
   }

   /*!
    * @brief Default constructor.
    */
   ~PeriodicId() = default;

   /*!
    * @brief Assignment operator.
    *
    * @param[in] rhs
    *
    * @return @c *this
    */
   constexpr PeriodicId&
   operator = (
      const PeriodicId& rhs) = default;

   /*!
    * @brief Assignment operator.
    *
    * @param[in] rhs
    *
    * @return @c *this
    */
   constexpr PeriodicId&
   operator = (
      const int& rhs)
   {
      d_value = rhs;
      return *this;
   }

   /*!
    * @brief Access the numerical value.
    */
   constexpr const int&
   getPeriodicValue() const
   {
      return d_value;
   }

   /*!
    * @brief Get the PeriodicId with a numerical value of zero.
    */
   static const PeriodicId&
   zero()
   {
      return s_zero_id;
   }

   /*!
    * @brief Return the invalid value for PeriodicId.
    */
   static const PeriodicId&
   invalidId()
   {
      return s_invalid_id;
   }

   /*!
    * @brief Returns True if the value is valid.
    */
   constexpr bool
   isValid() const
   {
      return d_value >= 0;
   }

   //@{

   //! @name Comparison with another PeriodicId.

   /*!
    * @brief Equality operator.
    *
    * All comparison operators compare the numerical value.
    *
    * @param[in] rhs
    */
   constexpr bool
   operator == (
      const PeriodicId& rhs) const
   {
      return d_value == rhs.d_value;
   }

   /*!
    * @brief Inequality operator.
    *
    * See note on comparison for operator==(const PeriodicId&);
    *
    * @param[in] rhs
    */
   constexpr bool
   operator != (
      const PeriodicId& rhs) const
   {
      return d_value != rhs.d_value;
   }

   /*!
    * @brief Less-than operator.
    *
    * See note on comparison for operator==(const PeriodicId&);
    *
    * @param[in] rhs
    */
   constexpr bool
   operator < (
      const PeriodicId& rhs) const
   {
      return d_value < rhs.d_value;
   }

   /*!
    * @brief Greater-than operator.
    *
    * See note on comparison for operator==(const PeriodicId&);
    *
    * @param[in] rhs
    */
   constexpr bool
   operator > (
      const PeriodicId& rhs) const
   {
      return d_value > rhs.d_value;
   }

   /*!
    * @brief Less-than-or-equal-to operator.
    *
    * See note on comparison for operator==(const PeriodicId&);
    *
    * @param[in] rhs
    */
   constexpr bool
   operator <= (
      const PeriodicId& rhs) const
   {
      return d_value <= rhs.d_value;
   }

   /*!
    * @brief Greater-thanor-equal-to operator.
    *
    * See note on comparison for operator==(const PeriodicId&);
    *
    * @param[in] rhs
    */
   constexpr bool
   operator >= (
      const PeriodicId& rhs) const
   {
      return d_value >= rhs.d_value;
   }

   //@}

   /*!
    * @brief Format and insert object into a stream.
    */
   friend std::ostream&
   operator << (
      std::ostream& co,
      const PeriodicId& r);

private:
   /*!
    * @brief Numerical value of the identifier.
    */
   int d_value;

   static constexpr int s_zero_val = 0;

   static constexpr int s_invalid_val = -1;

   /*!
    * @brief PeriodicId with a numerical value of zero.
    */
   static const PeriodicId s_zero_id;

   /*!
    * @brief Definition of invalid PeriodicId.
    */
   static const PeriodicId s_invalid_id;

};

}
}

#endif  // included_hier_PeriodicId
