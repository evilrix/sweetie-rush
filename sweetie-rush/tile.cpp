/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/sweetie.cpp
  * @author : evilrix
  * @date   : 09/37/2014
  * @brief  : Implements the sweetie class
  *
  */

#include <algorithm>

#include "sdl_error.hpp"
#include "tile.hpp"
#include "sweetie.hpp"

namespace sweetie_rush {

   tile::tile(sweetie_ptr const & swt, renderer const * ren, int x, int y)
      : swt_(swt)
      , ren_(ren)
      , rect_(SDL_Rect {x*dim, y*dim, dim, dim})
   {
      render_copy();
   }

   bool tile::operator == (tile const & rhs)
   {
      return swt_.get() == rhs.swt_.get();
   }

   tile::sweetie_ptr tile::operator->() const
   {
      return swt_;
   }

   void tile::swap(tile & lhs, tile & rhs)
   {
      std::swap(lhs.swt_, rhs.swt_);
      lhs.render_copy();
      rhs.render_copy();
   }

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

         SdlRuntimeError::ThrowOnFalse(
            0 == SDL_RenderFillRect(ren_->get(), &rect_));

         SdlRuntimeError::ThrowOnFalse(
            0 == SDL_RenderCopy(ren_->get(), swt_->get(), nullptr, &rect_));
      }
   }

   void tile::selected(bool const selected)
   {
      if(selected_ != selected)
      {
         selected_ = selected;
         render_copy();
      }
   }
}
