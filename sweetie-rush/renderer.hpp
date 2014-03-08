/**
 * @file renderer.hpp
 *
 * @brief Declares the renderer class.
 */

#pragma once

#include "sdl_base.hpp"
#include "window.hpp"

namespace sweetie_rush {

   class renderer :
      public sdl_base<SDL_Renderer, SDL_DestroyRenderer>
   {
      public:
         renderer(window const & win, int index, Uint32 flags);
   };

}
