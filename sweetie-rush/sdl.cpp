/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/sdl.cpp
  * @author : evilrix
  * @date   : 09/37/2014
  * @brief  : Implements the sdl class
  *
  */

#include "error.hpp"
#include "sdl.hpp"

namespace sweetie_rush {

   sdl::sdl()
   {
      RuntimeError::ThrowOnFalse(
         0 == SDL_Init(SDL_INIT_EVERYTHING),
         "Unable to initialise SDL"
      );
   }

   sdl::~sdl()
   {
      SDL_Quit();
   }

   void sdl::construct_singleton()
   {
      static auto && singleton = sdl();
   }

}
