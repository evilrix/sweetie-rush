/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/sdl_error.hpp
  * @author : evilrix
  * @date   : 09/19/2014
  * @brief  : Declares the sdl error class
  *
  */

#pragma once

#pragma once

#include "error.hpp"

namespace sweetie_rush {

   /**
    * @brief An error.
    *
    * @tparam exT Type of the exception.
    */

   template<typename exT>
   struct sdl_error
   {
      /**
       * @brief Throw on true.
       *
       * @param res The resource.
       */

      static
      void ThrowOnTrue(bool const res)
      {
         error<exT>::ThrowOnTrue(res, SDL_GetError());
      }

      /**
       * @brief Throw on false.
       *
       * @param res The resource.
       */

      static
      void ThrowOnFalse(bool const res)
      {
         error<exT>::ThrowOnFalse(res, SDL_GetError());
      }

      /**
       * @brief Throw on null.
       *
       * @param pvoid The pvoid.
       */

      static
      void ThrowOnNull(void const * pvoid)
      {
         error<exT>::ThrowOnNull(pvoid, SDL_GetError());
      }

      sdl_error() = delete;
   };

   using SdlRuntimeError = sdl_error<std::runtime_error>;
}
