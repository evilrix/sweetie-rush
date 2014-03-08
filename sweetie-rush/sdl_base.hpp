/**
 * @file sdl_base.hpp
 *
 * @brief Declares the sdl base class.
 */

#pragma once

#include <SDL2/SDL.h>

namespace sweetie_rush {

   template<typename sdlT, void (*deleterT)(sdlT *)>
   class sdl_base
   {
      public:
         using ptr_type = sdlT * ;

      public:
         sdl_base(ptr_type raw) : ptr_(raw) {}
         virtual ~sdl_base() { if(ptr_) { deleterT(ptr_); } };

      public:
         ptr_type get() const { return ptr_; }

      private:
         ptr_type ptr_;
   };

}
