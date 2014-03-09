/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/sdl_base.hpp
  * @author : evilrix
  * @date   : 09/36/2014
  * @brief  : Declares the sdl base class
  *
  */

#pragma once

#include <memory>
#include <functional>

#include <SDL2/SDL.h>

#include "error.hpp"

namespace sweetie_rush {

   /**
    * @brief Base class for SDL resources.
    *
    * @tparam sdlT Type of the sdl object.
    */

   template<typename sdlT>
   class sdl_base
   {
      public:

         /**
          * @brief Defines an alias representing type of the value.
          */

         typedef sdlT value_type;

         /**
          * @brief Defines an alias representing type of the pointer.
          */

         typedef value_type * ptr_type;

      public:

         /**
          * @brief Initializes a new instance of the sdl_base class.
          *
          * @param raw     The raw.
          * @param deleter The deleter.
          */

         sdl_base(ptr_type raw, std::function<void(ptr_type)> deleter)
            : ptr_(raw, deleter)
         {
            RuntimeError::ThrowOnNull(get(), SDL_GetError());
         }

         /**
          * @brief Finalizes an instance of the sdl_base class.
          */

         virtual ~sdl_base() = default;

      public:

         /**
          * @brief Gets the get.
          *
          * @return A ptr_type.
          */

         ptr_type get() const
         {
            return ptr_.get();
         }

      private:
         std::shared_ptr<value_type> ptr_;
   };

}
