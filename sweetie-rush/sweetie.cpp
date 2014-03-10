/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/sweetie.cpp
  * @author : evilrix
  * @date   : 09/37/2014
  * @brief  : Implements the sweetie class
  *
  */

#include "surface.hpp"
#include "sweetie.hpp"

namespace sweetie_rush {

   /*!
    * \brief Initializes a new instance of the blue> class.
    *
    * \tparam sweetie_enum::blue Type of the sweetie enum blue.
    * \param ren The ren.
    */

   template <>
   sweetie_<sweetie_enum::blue>::sweetie_(renderer const & ren)
      : sweetie(ren, surface("blue.png"))
   {
   }

   /*!
    * \brief Initializes a new instance of the green> class.
    *
    * \tparam sweetie_enum::green Type of the sweetie enum green.
    * \param ren The ren.
    */

   template <>
   sweetie_<sweetie_enum::green>::sweetie_(renderer const & ren)
      : sweetie(ren, surface("green.png"))
   {
   }

   /*!
    * \brief Initializes a new instance of the purple> class.
    *
    * \tparam sweetie_enum::purple Type of the sweetie enum purple.
    * \param ren The ren.
    */

   template <>
   sweetie_<sweetie_enum::purple>::sweetie_(renderer const & ren)
      : sweetie(ren, surface("purple.png"))
   {
   }

   /*!
    * \brief Initializes a new instance of the red> class.
    *
    * \tparam sweetie_enum::red Type of the sweetie enum red.
    * \param ren The ren.
    */

   template <>
   sweetie_<sweetie_enum::red>::sweetie_(renderer const & ren)
      : sweetie(ren, surface("red.png"))
   {
   }

   /*!
    * \brief Initializes a new instance of the yellow> class.
    *
    * \tparam sweetie_enum::yellow Type of the sweetie enum yellow.
    * \param ren The ren.
    */

   template <>
   sweetie_<sweetie_enum::yellow>::sweetie_(renderer const & ren)
      : sweetie(ren, surface("yellow.png"))
   {
   }
}
