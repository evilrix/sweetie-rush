/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/surface.hpp
  * @author : evilrix
  * @date   : 09/37/2014
  * @brief  : Declares the surface class
  *
  */

#pragma once

#include <string>

#include "sdl_base.hpp"

namespace sweetie_rush {

   /**
    * @brief A surface.
    */

   class surface
      : public sdl_base<SDL_Surface>
   {
      public:

         /**
          * @brief Initializes a new instance of the surface class.
          *
          * @param path Full pathname of the file.
          */

         surface(std::string const & path);
   };

}
