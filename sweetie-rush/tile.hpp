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

   /*!
    * \brief A tile.
    */

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

         bool operator == (tile const & rhs) const;

         /*!
          * \brief Inequality operator.
          *
          * \param rhs The right hand side.
          *
          * \return true if the parameters are not considered equivalent.
          */

         bool operator != (tile const & rhs) const;

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

         static void swap(tile & lhs, tile & rhs);

         /**
          * @brief Swaps the given right hand side.
          *
          * @param [in,out] rhs The right hand side.
          */

         void swap(tile & rhs);

         /**
          * @brief Selected the given selected.
          *
          * @param selected (Optional) the selected.
          */

         void selected(bool const selected = true);

         /**
          * @brief Toggle selected.
          */

         void toggle_selected();

         /**
          * @brief Query if this tile is selected.
          *
          * @return true if selected, false if not.
          */

         bool is_selected() const { return selected_; }

         /*!
          * \brief Get x coordinate.
          *
          * \return The x coordinate.
          */

         int get_x() const { return x_; }

         /*!
          * \brief Get y coordinate.
          *
          * \return The y coordinate.
          */

         int get_y() const { return y_; }

         /*!
          * \brief Blanks this tile.
          */

         void clear();

         /*!
          * \brief Query if this tile is clear.
          *
          * \return true if clear, false if not.
          */

         bool tile::is_clear() const;

      public:

         /*!
          * \brief X/Y coords.
          */

         struct coords
         {
            int x = -1;
            int y = -1;

            coords() = default;

            coords(int x, int y) : x(x), y(y) {}

            bool operator == (coords const & rhs) const
            {
               return x == rhs.x && y == rhs.y;
            }

            bool operator != (coords const & rhs) const
            {
               return !(*this == rhs);
            }
         };

      private:
         void render_copy() const;

      private:
         sweetie_ptr swt_;
         renderer const * ren_ = nullptr;
         int x_ = -1;
         int y_ = -1;
         bool selected_ = false;

   };


}
