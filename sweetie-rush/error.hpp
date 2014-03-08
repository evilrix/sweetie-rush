/**
 * @file error_utils.hpp
 *
 * @brief Declares the error utilities class.
 */

#pragma once

#include <stdexcept>

namespace sweetie_rush {
   template<typename exT>
   struct error
   {
      static
      void ThrowOnTrue(bool const res, std::string const & msg)
      {
         if(res)
         {
            throw exT(msg);
         }
      }

      static
      void ThrowOnFalse(bool const res, std::string const & msg)
      {
         ThrowOnTrue(!res, msg);
      }

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
