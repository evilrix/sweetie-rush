/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/window.cpp
  * @author : evilrix
  * @date   : 09/38/2014
  * @brief  : Implements the window class
  *
  */

#include "error.hpp"
#include "window.hpp"

namespace sweetie_rush {

   /*!
    * \brief Initializes a new instance of the window class.
    *
    * \param title The title.
    * \param x     The x coordinate.
    * \param y     The y coordinate.
    * \param w     The width.
    * \param h     The height.
    * \param flags The flags.
    */

   window::window(const char * title, int x, int y, int w,int h, Uint32 flags)
      : sdl_base(SDL_CreateWindow(title, x, y, w, h, flags), SDL_DestroyWindow)
   {

   }
}
