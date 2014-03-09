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

   template <>
   sweetie_<sweetie_enum::blue>::sweetie_(renderer const & ren)
      : sweetie(ren, surface("blue.png"))
   {
   }

   template <>
   sweetie_<sweetie_enum::green>::sweetie_(renderer const & ren)
      : sweetie(ren, surface("green.png"))
   {
   }

   template <>
   sweetie_<sweetie_enum::purple>::sweetie_(renderer const & ren)
      : sweetie(ren, surface("purple.png"))
   {
   }

   template <>
   sweetie_<sweetie_enum::red>::sweetie_(renderer const & ren)
      : sweetie(ren, surface("red.png"))
   {
   }

   template <>
   sweetie_<sweetie_enum::yellow>::sweetie_(renderer const & ren)
      : sweetie(ren, surface("yellow.png"))
   {
   }
}
