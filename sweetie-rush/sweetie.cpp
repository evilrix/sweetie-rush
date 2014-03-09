/**
 * @file sweetie.cpp
 *
 * @brief Implements the sweetie class.
 */

#include "surface.hpp"
#include "sweetie.hpp"

namespace sweetie_rush {

   template <>
   sweetie<sweetie_enum::blue>::sweetie(renderer const & ren)
      : texture(ren, surface("blue.png"))
   {
   }

   template <>
   sweetie<sweetie_enum::green>::sweetie(renderer const & ren)
      : texture(ren, surface("green.png"))
   {
   }

   template <>
   sweetie<sweetie_enum::purple>::sweetie(renderer const & ren)
      : texture(ren, surface("purple.png"))
   {
   }

   template <>
   sweetie<sweetie_enum::red>::sweetie(renderer const & ren)
      : texture(ren, surface("red.png"))
   {
   }

   template <>
   sweetie<sweetie_enum::yellow>::sweetie(renderer const & ren)
      : texture(ren, surface("yellow.png"))
   {
   }
}
