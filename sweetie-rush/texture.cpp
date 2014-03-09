/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/texture.cpp
  * @author : evilrix
  * @date   : 09/37/2014
  * @brief  : Implements the texture class
  *
  */

#include "error.hpp"
#include "texture.hpp"

namespace sweetie_rush {

   texture::texture(renderer const & ren, surface const & sur)
      : sdl_base(SDL_CreateTextureFromSurface(ren.get(), sur.get()),
                 SDL_DestroyTexture)
   {

   }

}
