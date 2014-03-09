/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/sweetie.hpp
  * @author : evilrix
  * @date   : 09/37/2014
  * @brief  : Declares the sweetie class
  *
  */

#pragma once

#include "sweetie.hpp"

namespace sweetie_rush {

   class tile
   {
      public:
         using sweetie_ptr = std::shared_ptr<sweetie>;
         static const int dim = 36;

      public:

         /**
          * @brief Initializes a new instance of the tile class.
          */

         tile() = default;

         /**
          * @brief Initializes a new instance of the tile class.
          *
          * @param swt The swt.
          * @param ren The ren.
          * @param x   The x coordinate.
          * @param y   The y coordinate.
          */

         tile(sweetie_ptr const & swt, renderer const * ren, int x, int y);

      public:

         /**
          * @brief Equality operator.
          *
          * @param rhs The right hand side.
          *
          * @return true if the parameters are considered equivalent.
          */

         bool operator == (tile const & rhs);

         /**
          * @brief Member dereference operator.
          *
          * @return The dereferenced object.
          */

         sweetie_ptr operator->() const;

      public:

         /**
          * @brief Swaps.
          *
          * @param [in,out] lhs The left hand side.
          * @param [in,out] rhs The right hand side.
          */

         static
         void swap(tile & lhs, tile & rhs);

      private:
         void render_copy() const;

      private:
         sweetie_ptr swt_;
         renderer const * ren_ = nullptr;
         int x_ = 0;
         int y_ = 0;
   };


}
