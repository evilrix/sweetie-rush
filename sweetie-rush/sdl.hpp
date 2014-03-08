/**
 * @file sdl.hpp
 *
 * @brief Declares the sdl class.
 */

#pragma once

#include <SDL2/SDL.h>

namespace sweetie_rush {

   class sdl
   {
      public:
         static void construct_singleton();

      private:
         sdl();
         ~sdl();

      private:
         sdl(sdl const &) = delete;
         sdl operator = (sdl const &) = delete;
   };

}
