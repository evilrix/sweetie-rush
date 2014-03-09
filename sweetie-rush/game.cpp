/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/game.cpp
  * @author : evilrix
  * @date   : 09/48/2014
  * @brief  : Implements the game class
  *
  */

#include <cstdlib>
#include <ctime>

#include <SDL2/SDL.h>

#include "game.hpp"

namespace sweetie_rush {

   game::game()
   {
      srand(static_cast<unsigned int>(time(0)));
   }

   void game::run()
   {
      auto && e = SDL_Event();
      auto quit = false;

      while (!quit)
      {
         while (SDL_PollEvent(&e))
         {
            if (e.type == SDL_QUIT)
            {
               quit = true;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
               brd_.on_mouse_click(e);
            }

            if (e.type == SDL_MOUSEMOTION)
            {
               brd_.on_mouse_motion(e);
            }
         }
      }

   }

}
