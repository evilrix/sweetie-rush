/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/surface.cpp
  * @author : evilrix
  * @date   : 09/37/2014
  * @brief  : Implements the surface class
  *
  */

#include <SDL2/SDL_image.h>

#include "error.hpp"
#include "surface.hpp"

namespace sweetie_rush {

   surface::surface(std::string const & path)
      : sdl_base(IMG_Load(path.c_str()), SDL_FreeSurface)
   {

   }
}
