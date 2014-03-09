/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/texture.hpp
  * @author : evilrix
  * @date   : 09/37/2014
  * @brief  : Declares the texture class
  *
  */

#pragma once

#include "sdl_base.hpp"
#include "renderer.hpp"
#include "surface.hpp"

namespace sweetie_rush {

   /**
    * @brief A texture.
    */

   class texture :
      public sdl_base<SDL_Texture>
   {
      public:

         /**
          * @brief Initializes a new instance of the texture class.
          *
          * @param ren The ren.
          * @param sur The sur.
          */

         texture(renderer const & ren, surface const & sur);
   };

}
