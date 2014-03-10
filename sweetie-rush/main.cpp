/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/main.cpp
  * @author : evilrix
  * @date   : 09/37/2014
  * @brief  : Implements the main class
  *
  */

#include <ctime>
#include <iostream>

#include <Windows.h>

#include "game.hpp"

namespace sweetie_rush {

   /*!
    * \brief Main entry-point for this application.
    */

   void main()
   {
      game().run();
   }
}

/*!
 * \brief Attach console.
 */

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

/*!
 * \brief Window main.
 *
 * \param parameter1 The first parameter.
 * \param parameter2 The second parameter.
 * \param parameter3 The third parameter.
 * \param parameter4 The fourth parameter.
 *
 * \return A CALLBACK.
 */

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
      srand(static_cast<unsigned int>(time(0)));
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
