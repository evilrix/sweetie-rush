/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/board.cpp
  * @author : evilrix
  * @date   : 09/37/2014
  * @brief  : Implements the board class
  *
  */

#include <cmath>
#include <utility>
#include <algorithm>
#include <memory>

#include "sweetie.hpp"
#include "board.hpp"

namespace sweetie_rush {

   auto const delay = 100; ///< Delay in ms for sweetie animation

   /*!
    * \brief Initializes a new instance of the board class.
    */

   board::board()
      : win_(window("Sweetie Rush!",
                    SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED,
                    board_siz, board_siz,
                    SDL_WINDOW_SHOWN))
      , ren_(renderer(
                win_, -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))
   {
      // Our sweeties, cached - used to repaint the board
      sweets_.push_back(std::shared_ptr<sweetie>(new sweetie_blue(ren_)));
      sweets_.push_back(std::shared_ptr<sweetie>(new sweetie_green(ren_)));
      sweets_.push_back(std::shared_ptr<sweetie>(new sweetie_purple(ren_)));
      sweets_.push_back(std::shared_ptr<sweetie>(new sweetie_red(ren_)));
      sweets_.push_back(std::shared_ptr<sweetie>(new sweetie_yellow(ren_)));

      // initialise the play aread
      initialise();

      // render the play area
      render();
   }

   /*!
    * \brief Fill col.
    *
    * \param x The x coordinate.
    * \param y The y coordinate.
    *
    * Fills the y-axis, starting from position y until full
    */

   void board::fill_col(int x, int y)
   {
      // The size of our sweeties are defined by this rectangle
      SDL_Rect tile_rect {x*36, y*36, tile_size, tile_size};

      // to iterate throught the loaded textures so as to create a play area
      auto itr = sweets_.end();

      // process the y-axis
      for(; y >= 0 ; --y)
      {

         // set rendering position
         tile_rect.y += y*36;

         // So, when we first create the board we want to make sure that no
         // more than two of the same sweeties are touching, otherwise we
         // start off the game awarding points to the player! The following
         // section of code ensure that can't happen.
         for(;;)
         {
            // once we've worked our way though our list of textures...
            if(itr == sweets_.end())
            {
               // ...shuffle them up and start again
               std::random_shuffle(sweets_.begin(), sweets_.end());
               itr = sweets_.begin();

               // Note: The reason for the shuffling rather than just using
               // a randomised index into the vector of tiles is to avoid
               // a situation where we have three tiles in a row. In this
               // case we need to pick a different texture, depending on how
               // poor the random number generator is we could get stuck in
               // a loop (possible, but unlikely infinate). By iterating a
               // list of random unique tiles we are guaranteed that, at
               // most, we'll have to skip two tiles. This is probably
               // overkill, but I have worked on systems whose RNG was so
               // bad they just repeatedly returned the same 4 numbers!!!
            }

            // assign our initial texture
            tiles_[x][y] = tile(*itr++, &ren_, x, y);

            // now make sure we're not adding a 3rd matching to the X-axis
            if(x >= 2)
            {
               if(tiles_[x][y] == tiles_[x-1][y] &&
                  tiles_[x][y] == tiles_[x-2][y])
               {
                  // three in a row, pick again
                  continue;
               }
            }

            // now make sure we're not adding a 3rd to the Y-axis
            if(y < 6)
            {
               if(tiles_[x][y] == tiles_[x][y+1] &&
                  tiles_[x][y] == tiles_[x][y+2])
               {
                  // three in a row, pick again
                  continue;
               }
            }

            // update the board
            render();

            // all good, break out of the try/repeat loop
            break;
         }
      }
   }

   /**
    * @brief Initialises this board.
    */

   void board::initialise()
   {
      // for each column, fill it
      for(auto x = 0 ; x < board_dim ; ++x)
      {
         fill_col(x, board_dim-1);
      }
   }

   /*!
    * \brief Renders this board.
    */

   void board::render() const
   {
      // (re-)render the play area
      SDL_RenderPresent(ren_.get());
      SDL_Delay(delay);
   }

   /*!
    * \brief Handles the drops.
    *
    * \param [in,out] pt   If non-null, the point.
    * \param [in,out] pcur If non-null, the pcur.
    *
    * Swaps out current tile for the next real tile above it, moving all times
    * down to fille the gaps and then adding new tiles to the column.
    *
    * TODO: as things drop they might create more matches so we should handle
    */

   void board::handle_drop(tile * pt, tile * pcur)
   {
      // firstly, remove matches and compact the space
      while(pcur->get_y() >= 0)
      {
         pt->blank();
         pt->swap(*pcur);

         render();

         if(pcur->get_y() - 1 < 0)
         {
            break;
         }

         pt = &tiles_[pt->get_x()][pt->get_y()-1];
         pcur = &tiles_[pcur->get_x()][pcur->get_y()-1];
      }

      // then fill the rest of the column with new sweeties
      if(pt->get_y() >= 0)
      {
         fill_col(pt->get_x(), pt->get_y());
      }
   }

   /*!
    * \brief Clears the y-axis of matches.
    *
    * \param this_click this clicked tile.
    *
    * \return true if it succeeds, false if it fails.
    */

   bool board::clear_y(coords const & this_click)
   {
      // find the start of the y-axis run
      auto & this_tile = tiles_[this_click.x][this_click.y];
      tile * pt = &this_tile;
      tile * pt_next = pt;

      while(pt_next)
      {
         pt_next = pt->get_y() + 1 < board_dim
                   ? &tiles_[pt->get_x()][pt->get_y() + 1] : nullptr;

         if(pt_next && *pt_next != *pt)
         {
            pt_next = nullptr;
         }

         if(pt_next)
         {
            pt = pt_next;
         }
      }

      // find the end of the y-axis run
      auto pcur = pt;

      while(pcur->get_y() > 0 && *pcur == *pt)
      {
         pcur = &tiles_[pcur->get_x()][pcur->get_y()-1];
      }

      // do we have 3 or more in a row?
      auto drop = ((pt->get_y() - pcur->get_y()) >= 2);

      // remove the matches
      if(drop)
      {
         handle_drop(pt, pcur);
      }

      return drop;
   }

   /*!
    * \brief Clears the x-axis of matches.
    *
    * \param this_click this clicked tile.
    *
    * \return true if it succeeds, false if it fails.
    */

   bool board::clear_x(coords const & this_click)
   {
      // find the start of the x-axis run
      auto & this_tile = tiles_[this_click.x][this_click.y];

      tile * pt = &this_tile;
      tile * pt_next = pt;

      while(pt_next)
      {
         pt_next = pt->get_x() + 1 < board_dim
                   ? &tiles_[pt->get_x() + 1][pt->get_y()] : nullptr;

         if(pt_next && *pt_next != *pt)
         {
            pt_next = nullptr;
         }

         if(pt_next)
         {
            pt = pt_next;
         }
      }

      // find the end of the x-axis run
      auto pcur = pt;

      while(pcur->get_x() > 0)
      {
         auto tmp = &tiles_[pcur->get_x()-1][pcur->get_y()];

         if(*tmp != *pcur) { break; }

         pcur = tmp;
      }

      // do we have 3 or more in a row?
      auto drop = ((pt->get_x() - pcur->get_x()) >= 2);

      // remove the candiate matches
      if(drop)
      {
         // for each item on the x-axis we remove we do an y-axis drop
         do
         {
            bool cleared = false;

            // if the current x-axis we're going to clear is also the tie
            // clicked we also want to check and clear the y-axis
            if(pcur == &this_tile)
            {
               cleared = clear_y(this_click);
            }

            // if we removed nothing from the y-axis
            if(!cleared)
            {
               // if this is the last row just add new
               if(pcur->get_y() == 0)
               {
                  fill_col(pcur->get_x(), pcur->get_y());
               }
               // else, clear and compact matches
               else
               {
                  handle_drop(pcur, &tiles_[pcur->get_x()][pcur->get_y()-1]);
               }
            }

            // if we have more on the x-axis, process them
            if(pcur->get_x() < board_dim - 1)
            {
               pcur = &tiles_[pcur->get_x()+1][pcur->get_y()];
            }
         }
         while(pcur->get_x() < (board_dim-1) && pcur->get_x() <= pt->get_x());
      }
      // there were no x-axis candidates, so just clean the y-axis
      else
      {
         // clean what was clicked
         drop = clear_y(this_click);

         if(!drop || this_click.y != last_click_.y)
         {
            // clean the other tile, too
            drop = drop || clear_y(last_click_);
         }
      }

      return drop;
   }

   /*!
    * \brief Clears the xy-axis of matches.
    *
    * \param this_click this clicked tile.
    */

   void board::clear_xy(coords const & this_click)
   {
      // get this tile and the last tile clicked
      auto & this_tile = tiles_[this_click.x][this_click.y];
      auto & last_tile = tiles_[last_click_.x][last_click_.y];

      // clear selections on both tiles
      last_tile.selected(false);
      this_tile.selected(false);

      // look for and file matches for clicked tile
      auto match = clear_x(this_click);

      if(!match || this_click.x != last_click_.x)
      {
         // look for and file matches for other tile
         match = match || clear_x(last_click_);
      }

      // did we file any matches?
      if(!match)
      {
         //...nope, so swap tiles back again
         auto & this_tile = tiles_[this_click.x][this_click.y];
         auto & last_tile = tiles_[last_click_.x][last_click_.y];

         last_tile.swap(this_tile);
      }

      // render the board
      render();
   }

   /*!
    * \brief Handles mouse click signals.
    *
    * \param e The SDL_Event const &amp; to process.
    */

   void board::on_mouse_click(SDL_Event const & e)
   {
      swipe_ok = true;

      if(e.button.button & SDL_BUTTON_LEFT)
      {
         auto this_click = coords { e.button.x, e.button.y };

         // get the position down to tile granularity
         this_click.x /= tile_size;
         this_click.y /= tile_size;

         // Toggle select on this tile...
         auto & this_tile = tiles_[this_click.x][this_click.y];
         this_tile.toggle_selected();

         // If the current tile is selected we move it
         if(this_tile.is_selected())
         {
            // if we moved tiles try cleaning matches
            if(move_tile(this_click))
            {
               clear_xy(this_click);
               last_click_ = coords {-1, -1};
            }
            // no tile toggle this time, remember this tile just clicked
            else
            {
               last_click_ = this_click;
            }
         }
         else
         {
            // no tiles selected, unset last click state
            last_click_ = coords {-1, -1};
         }

         // redraw board
         render();
      }
   }

   /*!
    * \brief Handles mouse motion signals.
    *
    * \param e The SDL_Event const &amp; to process.
    */

   void board::on_mouse_motion(SDL_Event const & e)
   {
      if(e.motion.state & SDL_BUTTON_LEFT)
      {
         auto this_click = coords { e.button.x, e.button.y };

         // get the position down to tile granularity
         this_click.x /= tile_size;
         this_click.y /= tile_size;

         // if swipes are allowed
         if(swipe_ok)
         {
            // handle moving tiles
            if(move_tile(this_click))
            {
               clear_xy(this_click);
               last_click_ = coords {-1, -1};
            }
            else
            {
               last_click_ = this_click;
            }
         }

         render();
      }
   }

   /*!
    * \brief Move tile.
    *
    * \param this_click this click.
    *
    * \return true if it succeeds, false if it fails.
    */

   bool board::move_tile(coords const & this_click)
   {
      bool moved = false;
      auto & this_tile = tiles_[this_click.x][this_click.y];

      // if this click differs from the last...
      if(this_click.x != last_click_.x || this_click.y != last_click_.y)
      {
         // if we've perviously clicked a tile...
         if(last_click_.x >= 0 && last_click_.y >= 0)
         {
            auto & last_tile = tiles_[last_click_.x][last_click_.y];

            // get the x/y axis difference between this and last
            auto const x_diff = abs(this_click.x-last_click_.x);
            auto const y_diff = abs(this_click.y-last_click_.y);

            // if this tile is adjacent vertically or horizontally
            if((1 == x_diff && 1 != y_diff) ||
               (1 != x_diff && 1 == y_diff))
            {
               // swap the tiles
               last_tile.swap(this_tile);
               moved = true;

               // prevent more swiping until mouse unclicked
               swipe_ok = false;
            }

            // unselect the previous tile
            last_tile.selected(false);
         }
      }

      // render any changes to the board
      render();

      return moved;
   }
}
