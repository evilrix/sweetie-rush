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

   class sweetie : public texture
   {
      public:

         /**
          * @brief Initializes a new instance of the sweetie class.
          *
          * @param ren The ren.
          */

         sweetie(renderer const & ren, surface const & sur)
            : texture(ren, sur)
         {
         }

      public:

         /**
          * @brief Gets the tag.
          *
          * @return A sweetie_enum.
          */

         virtual sweetie_enum tag() const = 0;
   };

   /**
    * @brief A sweetie.
    *
    * @tparam swen Type of the sweetie enumeration.
    */

   template<sweetie_enum swen>
   class sweetie_ : public sweetie
   {
      public:

         /**
          * @brief Initializes a new instance of the sweetie class.
          *
          * @param ren The ren.
          */

         sweetie_(renderer const & ren);

      public:

         /**
          * @brief Gets the tag.
          *
          * @return A sweetie_enum.
          */

         sweetie_enum tag() const override { return swen; }
   };

   /**
     * @brief Types of sweetie.
     */

   using sweetie_blue = sweetie_<sweetie_enum::blue>;
   using sweetie_green = sweetie_<sweetie_enum::green>;
   using sweetie_purple = sweetie_<sweetie_enum::purple>;
   using sweetie_red = sweetie_<sweetie_enum::red>;
   using sweetie_yellow = sweetie_<sweetie_enum::yellow>;

}
