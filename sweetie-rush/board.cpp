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
#include <vector>

#include "sweetie.hpp"
#include "board.hpp"

namespace sweetie_rush {

   board::board()
      : win_(window("Sweetie Rush!",
                    SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED,
                    board_siz, board_siz,
                    SDL_WINDOW_SHOWN))
      , ren_(renderer(
                win_, -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))
   {
      // initialise the play aread
      initialise();

      // render the play area
      render();
   }

   /**
    * @brief Initialises this board.
    */

   void board::initialise()
   {
      // Load assets (sweetie images)
      //
      // NB: -
      // Unfortunately, Visual Studio 2013 has a known defect, which means you
      // can't use initialization lists to construct STL containers with shared
      // pointers. It converts them to weak pointers, which causes the memory
      // to be deleted both when the original shared_ptr goes out of scope and
      // also when the weak pointer goes out of scope. This has been fixed by
      // Microsoft but the patch has yet to be released. In the mean time it's
      // necessary to construct a vector the old fashioned way =/
      auto && sweets = std::vector<std::shared_ptr<sweetie>>();
      sweets.push_back(std::shared_ptr<sweetie>(new sweetie_blue(ren_)));
      sweets.push_back(std::shared_ptr<sweetie>(new sweetie_green(ren_)));
      sweets.push_back(std::shared_ptr<sweetie>(new sweetie_purple(ren_)));
      sweets.push_back(std::shared_ptr<sweetie>(new sweetie_red(ren_)));
      sweets.push_back(std::shared_ptr<sweetie>(new sweetie_yellow(ren_)));

      // The size of our sweeties are defined by this rectangle
      SDL_Rect tile_rect {0, 0, tile_size, tile_size};

      // to iterate throught the loaded textures so as to create a play area
      auto itr = sweets.end();

      // process the Y-axis
      for(auto y = 0 ; y < 8 ; ++y)
      {
         tile_rect.x = 0;

         // process the X-axis
         for(auto x = 0 ; x < 8 ; ++x)
         {
            // So, when we first create the board we want to make sure that no
            // more than two of the same sweeties are touching, otherwise we
            // start off the game awarding points to the player! The following
            // section of code ensure that can't happen.
            for(;;)
            {
               // once we've worked our way though our list of textures...
               if(itr == sweets.end())
               {
                  // ...shuffle them up and start again
                  std::random_shuffle(sweets.begin(), sweets.end());
                  itr = sweets.begin();

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

               // now make sure we're not adding a 3rd to the X-axis
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
               if(y >= 2)
               {
                  if(tiles_[x][y] == tiles_[x][y-1] &&
                     tiles_[x][y] == tiles_[x][y-2])
                  {
                     // three in a row, pick again
                     continue;
                  }
               }

               // all good, break out of the try/repeat loop
               break;
            }

            tile_rect.x += 36;
         }

         tile_rect.y += 36;
      }
   }

   void board::render() const
   {
      // (re-)render the play area
      SDL_RenderPresent(ren_.get());
   }

   bool board::handle_drop(tile * pt)
   {
      auto pcur = pt;

      while(pcur->get_y() > 0 && *pcur == *pt)
      {
         pcur = &tiles_[pcur->get_x()][pcur->get_y()-1];
      }

      auto drop = ((pt->get_y() - pcur->get_y()) > 2);

      if(drop)
      {
         while(pcur->get_y() >= 0)
         {
            pt->blank();
            pt->swap(*pcur);

            render();
            SDL_Delay(500);

            if(pcur->get_y() - 1 < 0)
            {
               break;
            }

            pt = &tiles_[pt->get_x()][pt->get_y()-1];
            pcur = &tiles_[pcur->get_x()][pcur->get_y()-1];
         }
      }

      return drop;
   }

   void board::score_move(coords const & this_click)
   {
      auto & this_tile = tiles_[this_click.x][this_click.y];
      auto & last_tile = tiles_[last_click_.x][last_click_.y];

      last_tile.selected(false);
      this_tile.selected(false);

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

      if(!handle_drop(pt))
      {
         last_tile.swap(this_tile);
      }

      render();
      SDL_Delay(500);
   }

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
            if(move_tile(this_click))
            {
               score_move(this_click);
               last_click_ = coords {-1, -1};
            }
            else
            {
               last_click_ = this_click;
            }
         }
         else
         {
            last_click_ = coords {-1, -1};
         }

         render();
      }
   }

   void board::on_mouse_motion(SDL_Event const & e)
   {
      if(e.motion.state & SDL_BUTTON_LEFT)
      {
         auto this_click = coords { e.button.x, e.button.y };

         // get the position down to tile granularity
         this_click.x /= tile_size;
         this_click.y /= tile_size;

         if(swipe_ok)
         {
            if(move_tile(this_click))
            {
               score_move(this_click);
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

            // look for any three-in-a-line match

            // unselect the previous time
            last_tile.selected(false);
         }
      }

      return moved;
   }
}
