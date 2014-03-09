/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/renderer.hpp
  * @author : evilrix
  * @date   : 09/36/2014
  * @brief  : Declares the renderer class
  *
  */

#pragma once

#include "sdl_base.hpp"
#include "window.hpp"

namespace sweetie_rush {

   /**
    * @brief A renderer.
    */

   class renderer :
      public sdl_base<SDL_Renderer>
   {
      public:

         /**
          * @brief Initializes a new instance of the renderer class.
          *
          * @param win   The window.
          * @param index Zero-based index of the.
          * @param flags The flags.
          */

         renderer(window const & win, int index, Uint32 flags);
   };

}
