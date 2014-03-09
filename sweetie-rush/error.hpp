/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/error.hpp
  * @author : evilrix
  * @date   : 09/36/2014
  * @brief  : Declares the error class
  *
  */

#pragma once

#include <stdexcept>

namespace sweetie_rush {

   /**
    * @brief An error.
    *
    * @tparam exT Type of the exception.
    */

   template<typename exT>
   struct error
   {
      /**
       * @brief Throw on true.
       *
       * @exception exT Thrown when an ex t error condition occurs.
       *
       * @param res The resource.
       * @param msg The message.
       */

      static
      void ThrowOnTrue(bool const res, std::string const & msg)
      {
         if(res)
         {
            throw exT(msg);
         }
      }

      /**
       * @brief Throw on false.
       *
       * @param res The resource.
       * @param msg The message.
       */

      static
      void ThrowOnFalse(bool const res, std::string const & msg)
      {
         ThrowOnTrue(!res, msg);
      }

      /**
       * @brief Throw on null.
       *
       * @param pvoid The pvoid.
       * @param msg   The message.
       */

      static
      void ThrowOnNull(void const * pvoid, std::string const & msg)
      {
         ThrowOnTrue(nullptr == pvoid, msg);
      }

      error() = delete;
   };

   using RuntimeError = error<std::runtime_error>;
   using LogicError = error<std::logic_error>;
}
