/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/sdl.hpp
  * @author : evilrix
  * @date   : 09/36/2014
  * @brief  : Declares the sdl class
  *
  */

#pragma once

#include <SDL2/SDL.h>

namespace sweetie_rush {

   /**
    * @brief Meyers' Singleton class used to initialise the SDL.
    */

   class sdl
   {
      public:

         /**
          * @brief Construct singleton.
          */

         static sdl const & initialize();

      private:

         /*!
          * \brief Initializes a new instance of the sdl class.
          */

         sdl();

         /*!
          * \brief Finalizes an instance of the sdl class.
          */

         ~sdl();

      private:
         sdl(sdl const &) = delete;
         sdl operator = (sdl const &) = delete;
   };

}
