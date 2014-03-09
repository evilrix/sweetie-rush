/**
 * @file sweetie.h
 *
 * @brief Declares the sweetie class.
 */

#pragma once

#include "renderer.hpp"
#include "texture.hpp"

namespace sweetie_rush {

   enum class sweetie_enum
   {
      blue,
      green,
      purple,
      red,
      yellow
   };

   template<sweetie_enum swen>
   class sweetie : public texture
   {
      public:
         static const sweetie_enum tag = swen;

      public:
         sweetie(renderer const & ren);
   };

   using sweetie_blue = sweetie<sweetie_enum::blue>;
   using sweetie_green = sweetie<sweetie_enum::green>;
   using sweetie_purple = sweetie<sweetie_enum::purple>;
   using sweetie_red = sweetie<sweetie_enum::red>;
   using sweetie_yellow = sweetie<sweetie_enum::yellow>;

}
