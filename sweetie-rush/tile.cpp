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

   tile::tile(sweetie_ptr const & swt, renderer const * ren, int x, int y)
      : swt_(swt)
      , ren_(ren)
      , x_(x)
      , y_(y)
      , selected_(false)
   {
      render_copy();
   }

   bool tile::operator == (tile const & rhs) const
   {
      return swt_->tag() == rhs.swt_->tag();
   }

   bool tile::operator != (tile const & rhs) const
   {
      return !(swt_->tag() == rhs.swt_->tag());
   }

   tile::sweetie_ptr tile::operator->() const
   {
      return swt_;
   }

   void tile::swap(tile & rhs)
   {
      std::swap(swt_, rhs.swt_);
      render_copy();
      rhs.render_copy();
   }

   void tile::swap(tile & lhs, tile & rhs)
   {
      lhs.swt_.swap(rhs.swt_);
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

   void tile::selected(bool const selected)
   {
      if(selected_ != selected)
      {
         selected_ = selected;
         render_copy();
      }
   }

   void tile::toggle_selected()
   {
      selected(!selected_);
   }
}
