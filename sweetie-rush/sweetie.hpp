/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/sweetie.hpp
  * @author : evilrix
  * @date   : 09/37/2014
  * @brief  : Declares the sweetie class
  *
  */

#pragma once

#include "renderer.hpp"
#include "texture.hpp"

namespace sweetie_rush {

   /**
    * @brief Values that represent sweeties.
    */

   enum class sweetie_enum
   {
      blue,
      green,
      purple,
      red,
      yellow
   };

   /**
    * @brief A sweetie.
    *
    * @tparam swen Type of the sweetie enumeration.
    */

   template<sweetie_enum swen>
   class sweetie : public texture
   {
      public:
         static const sweetie_enum tag = swen;  ///< The tag

      public:
         sweetie(renderer const & ren);
   };

   /**
     * @brief Types of sweetie.
     */

   using sweetie_blue = sweetie<sweetie_enum::blue>;
   using sweetie_green = sweetie<sweetie_enum::green>;
   using sweetie_purple = sweetie<sweetie_enum::purple>;
   using sweetie_red = sweetie<sweetie_enum::red>;
   using sweetie_yellow = sweetie<sweetie_enum::yellow>;

}
