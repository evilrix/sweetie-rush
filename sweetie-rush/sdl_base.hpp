/**
 * @file sdl_base.hpp
 *
 * @brief Declares the sdl base class.
 */

#pragma once

#include <memory>
#include <functional>

#include <SDL2/SDL.h>

#include "error.hpp"

namespace sweetie_rush {

   template<typename sdlT>
   class sdl_base
   {
      public:
         typedef sdlT value_type;
         typedef value_type * ptr_type;

      public:
         sdl_base(ptr_type raw, std::function<void(ptr_type)> deleter)
            : ptr_(raw, deleter)
         {
            RuntimeError::ThrowOnNull(get(), SDL_GetError());
         }

         virtual ~sdl_base() {};

      public:
         ptr_type get() const { return ptr_.get(); }

      private:
         std::shared_ptr<value_type> ptr_;
   };

}
