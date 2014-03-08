/**
 * @file main.cpp
 *
 * @brief Implements the main class.
 */

#include <stdexcept>
#include <iostream>
#include <string>

#include <Windows.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sdl.hpp"
#include "window.hpp"
#include "renderer.hpp"
#include "surface.hpp"
#include "texture.hpp"
#include "error.hpp"

namespace sweetie_rush {

   void main()
   {
      sdl::construct_singleton();
      auto && img = IMG_Load("assets/blue.png");

      auto && win = window("Hello World!", 100, 100, 640, 480,
                           SDL_WINDOW_SHOWN);

      auto && ren = renderer(
                       win, -1,
                       SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

      auto && sur = surface("assets/blue.png");

      auto && tex = texture(ren, sur);

      SDL_RenderCopy(ren.get(), tex.get(), NULL, NULL);
      SDL_RenderPresent(ren.get());

      SDL_Delay(2000);
   }
}

void attach_console()
{
   bool attached = AttachConsole(ATTACH_PARENT_PROCESS) != 0;

#if !defined(NDEBUG)

   if (!attached)
   {
      attached = AllocConsole() != 0;
   }

#endif

   if (attached)
   {
      freopen("CON", "w", stdout);
      freopen("CON", "r", stdin);
      freopen("CON", "w", stderr);
   }
}


int CALLBACK WinMain(
   HINSTANCE /* hInstance */,
   HINSTANCE /* hPrevInstance */,
   LPSTR /* lpCmdLine */,
   int /* nCmdShow */
)
{
   int exitCode = 0;

   try
   {
      attach_console();
      sweetie_rush::main();
   }
   catch(std::exception const & e)
   {
      std::cerr << e.what() << std::endl;
   }
   catch(...)
   {
      std::cerr << "Unknown error" << std::endl;
   }

   return exitCode;
}
