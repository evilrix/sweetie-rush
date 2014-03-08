/**
 * @file renderer.cpp
 *
 * @brief Implements the renderer class.
 */

#include "error.hpp"
#include "renderer.hpp"

namespace sweetie_rush {

   renderer::renderer(
      window const & win, int index, Uint32 flags
   )
      : sdl_base(SDL_CreateRenderer(win.get(), index,flags))
   {
      RuntimeError::ThrowOnNull(
         get(), std::string("Unable to create renderer")
      );
   }
}
