/**
 * @file surface.cpp
 *
 * @brief Implements the surface class.
 */

#include <SDL2/SDL_image.h>

#include "error.hpp"
#include "surface.hpp"

namespace sweetie_rush {

   surface::surface(std::string const & path)
      : sdl_base(IMG_Load(path.c_str()))
   {
      RuntimeError::ThrowOnNull(
         get(), "Unable to create surface: " + path
      );
   }
}
