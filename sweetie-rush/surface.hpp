/**
 * @file surface.hpp
 *
 * @brief Declares the surface class.
 */

#pragma once

#include <string>

#include "sdl_base.hpp"

namespace sweetie_rush {

   class surface
      : public sdl_base<SDL_Surface, SDL_FreeSurface>
   {
      public:
         surface(std::string const & path);
   };

}
