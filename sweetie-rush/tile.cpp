/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/sweetie.cpp
  * @author : evilrix
  * @date   : 09/37/2014
  * @brief  : Implements the sweetie class
  *
  */

#include <algorithm>
#include <utility>

#include "sdl_error.hpp"
#include "tile.hpp"
#include "sweetie.hpp"

namespace sweetie_rush {

   /*!
    * \brief Initializes a new instance of the tile class.
    *
    * \param swt The swt.
    * \param ren The ren.
    * \param x   The x coordinate.
    * \param y   The y coordinate.
    */

   tile::tile(sweetie_ptr const & swt, renderer const * ren, int x, int y)
      : swt_(swt)
      , ren_(ren)
      , x_(x)
      , y_(y)
      , selected_(false)
   {
      render_copy();
   }

   /*!
    * \brief Equality operator.
    *
    * \param rhs The right hand side.
    *
    * \return true if the parameters are considered equivalent.
    */

   bool tile::operator == (tile const & rhs) const
   {
      if(!swt_ || !rhs.swt_)
      {
         return false;
      }

      return swt_->tag() == rhs.swt_->tag();
   }

   /*!
    * \brief Inequality operator.
    *
    * \param rhs The right hand side.
    *
    * \return true if the parameters are not considered equivalent.
    */

   bool tile::operator != (tile const & rhs) const
   {

      return !(*this == rhs);
   }

   /*!
    * \brief Member dereference operator.
    *
    * \return The dereferenced object.
    */

   tile::sweetie_ptr tile::operator->() const
   {
      return swt_;
   }

   /*!
    * \brief Swaps the given right hand side.
    *
    * \param [in,out] rhs The right hand side.
    */

   void tile::swap(tile & rhs)
   {
      std::swap(swt_, rhs.swt_);
      render_copy();
      rhs.render_copy();
   }

   /*!
    * \brief Swaps.
    *
    * \param [in,out] lhs The left hand side.
    * \param [in,out] rhs The right hand side.
    */

   void tile::swap(tile & lhs, tile & rhs)
   {
      lhs.swt_.swap(rhs.swt_);
   }

   /*!
    * \brief Renders the copy.
    */

   void tile::render_copy() const
   {
      if(ren_)
      {
         SdlRuntimeError::ThrowOnFalse(
            0 == SDL_SetRenderDrawColor(ren_->get(),
                                        selected_ ? 0xFF : 0x00,
                                        0x00,
                                        0x00,
                                        SDL_ALPHA_OPAQUE));

         auto && rect = SDL_Rect {x_*dim, y_*dim, dim, dim};

         SdlRuntimeError::ThrowOnFalse(
            0 == SDL_RenderFillRect(ren_->get(), &rect));

         if(swt_)
         {
            SdlRuntimeError::ThrowOnFalse(
               0 == SDL_RenderCopy(ren_->get(), swt_->get(), nullptr, &rect));
         }
      }
   }

   /*!
    * \brief Selected the given selected.
    *
    * \param selected The selected.
    */

   void tile::selected(bool const selected)
   {
      if(selected_ != selected)
      {
         selected_ = selected;
         render_copy();
      }
   }

   /*!
    * \brief Toggle selected.
    */

   void tile::toggle_selected()
   {
      selected(!selected_);
   }

   void tile::clear()
   {
      swt_.reset();
      render_copy();
   }

   bool tile::is_clear() const
   {
      return swt_ == nullptr;
   }
}
