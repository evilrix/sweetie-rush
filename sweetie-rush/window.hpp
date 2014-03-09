#pragma once

#include "sdl_base.hpp"

namespace sweetie_rush {

   class window :
      public sdl_base<SDL_Window>
   {
      public:
         window(const char * title, int x, int y, int w, int h, Uint32 flags);
   };

}
