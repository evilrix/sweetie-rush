/**
 * @file texture.cpp
 *
 * @brief Implements the texture class.
 */

#include "error.hpp"
#include "texture.hpp"

namespace sweetie_rush {

   texture::texture(renderer const & ren, surface const & sur)
      : sdl_base(SDL_CreateTextureFromSurface(ren.get(), sur.get()))
   {
      RuntimeError::ThrowOnNull(
         get(), std::string("Unable to create texture")
      );
   }
}
