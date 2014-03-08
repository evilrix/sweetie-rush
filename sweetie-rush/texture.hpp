/**
 * @file texture.hpp
 *
 * @brief Declares the texture class.
 */

#pragma once

#include "sdl_base.hpp"
#include "renderer.hpp"
#include "surface.hpp"

namespace sweetie_rush {

   class texture :
      public sdl_base<SDL_Texture, SDL_DestroyTexture>
   {
      public:
         texture(renderer const & ren, surface const & sur);
   };

}
