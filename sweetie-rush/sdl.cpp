/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/sdl.cpp
  * @author : evilrix
  * @date   : 09/37/2014
  * @brief  : Implements the sdl class
  *
  */

#include "sdl_error.hpp"
#include "sdl.hpp"

namespace sweetie_rush {

   /*!
    * \brief Initializes a new instance of the sdl class.
    */

   sdl::sdl()
   {
      SdlRuntimeError::ThrowOnFalse(0 == SDL_Init(SDL_INIT_EVERYTHING));
   }

   /*!
    * \brief Finalizes an instance of the sdl class.
    */

   sdl::~sdl()
   {
      SDL_Quit();
   }

   /*!
    * \brief Initializes this sdl.
    *
    * \return A const&amp;
    */

   sdl const & sdl::initialize()
   {
      static auto && singleton = sdl();
      return singleton;
   }

   namespace {
      // initializes the SDL framework before main() is called
      sdl const & sdl_singleton = sdl::initialize();
   }

}
