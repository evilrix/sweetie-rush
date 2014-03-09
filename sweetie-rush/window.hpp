/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/window.hpp
  * @author : evilrix
  * @date   : 09/37/2014
  * @brief  : Declares the window class
  *
  */

#pragma once

#include "sdl_base.hpp"

namespace sweetie_rush {

   /**
    * @brief A window.
    */

   class window :
      public sdl_base<SDL_Window>
   {
      public:

         /**
          * @brief Initializes a new instance of the window class.
          *
          * @param title The title.
          * @param x     The x coordinate.
          * @param y     The y coordinate.
          * @param w     The width.
          * @param h     The height.
          * @param flags The flags.
          */

         window(const char * title, int x, int y, int w, int h, Uint32 flags);
   };

}
