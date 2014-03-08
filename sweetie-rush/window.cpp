/**
 * @file window.cpp
 *
 * @brief Implements the window class.
 */

#include "error.hpp"
#include "window.hpp"

namespace sweetie_rush {

   window::window(
      const char * title,
      int x, int y, int w,
      int h, Uint32 flags
   )
      : sdl_base(SDL_CreateWindow(title, x, y, w, h, flags))
   {
      RuntimeError::ThrowOnNull(
         get(), std::string("Unable to create window: ") + title
      );
   }
}
