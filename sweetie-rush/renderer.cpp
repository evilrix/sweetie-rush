/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/renderer.cpp
  * @author : evilrix
  * @date   : 09/37/2014
  * @brief  : Implements the renderer class
  *
  */

#include "renderer.hpp"

namespace sweetie_rush {

   renderer::renderer(window const & win, int index, Uint32 flags)
      : sdl_base(SDL_CreateRenderer(win.get(), index,flags),
                 SDL_DestroyRenderer)
   {

   }

}
