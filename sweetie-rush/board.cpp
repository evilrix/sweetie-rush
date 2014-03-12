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

   /*!
    * \brief Callback, called when the quit.
    *
    * \param interval            The interval.
    * \param [in,out] parameter2 Unused.
    *
    * \return An Uint32.
    */

   Uint32 quit_callback(Uint32 interval, void * /* param */)
   {
      SDL_Event event;
      event.type = SDL_QUIT;
      SDL_PushEvent(&event);
      return interval;
   }

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

      // start the game's timer set for 1 minute
      SdlRuntimeError::ThrowOnTrue(
         0 == SDL_AddTimer(60*1000, quit_callback, nullptr));
   }

   /*!
    * \brief Fill col.
    *
    * \param ords    The ords.
    * \param animate The animate.
    */

   void board::fill_col(tile::coords const & ords, bool const animate)
   {
      int const x = ords.x;
      int y = ords.y;

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

            // animate filling the board?
            if(animate)
            {
               render();
            }

            // all good, break out of the try/repeat loop
            break;
         }
      }

      if(!animate)
      {
         render(false);
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
         fill_col(tile::coords(x, board_dim-1), false);
      }

      // render the play area
      render();
   }

   /*!
    * \brief Renders this board.
    */

   void board::render(bool const delay) const
   {
      // (re-)render the play area
      SDL_RenderPresent(ren_.get());

      if(delay)
      {
         SDL_Delay(50);
      }
   }

   /*!
    * \brief Scans for matches.
    */

   bool board::scan_for_matches(std::set<tile *> & matches)
   {
      // Scans both the verticle and horizontal axis' of the board and finds
      // all matches. These are put into a set for processing, later.
      for(auto o = 0 ; o < board_dim ; ++o)
      {
         auto last_x = 0;
         auto last_y = 0;

         for(auto i = 0 ; i <= board_dim ; ++i)
         {
            if(i == board_dim || tiles_[o][i] != tiles_[o][last_y])
            {
               if(i - last_y >2)
               {
                  for(auto z = last_y ; z < i ; ++z)
                  {
                     if(!tiles_[o][z].is_clear())
                     {
                        matches.insert(&tiles_[o][z]);
                     }
                  }
               }

               last_y = i;
            }

            if(i == board_dim || tiles_[i][o] != tiles_[last_x][o])
            {
               if(i - last_x >2)
               {
                  for(auto z = last_x ; z < i ; ++z)
                  {
                     if(!tiles_[o][z].is_clear())
                     {
                        matches.insert(&tiles_[z][o]);
                     }
                  }
               }

               last_x = i;
            }
         }
      }

      return !matches.empty();
   }

   /*!
    * \brief Rebuild the column.
    *
    * \param x The x coordinate.
    */

   void board::rebuild_col(tile::coords const & ords)
   {
      auto tort = ords.y;
      auto hare = ords.y;

      while(hare > 0)
      {
         while(tort > 0 && !tiles_[ords.x][tort].is_clear())
         {
            if(hare > --tort)
            {
               hare = tort;
            }
         }

         while(hare >= 0 && tiles_[ords.x][hare].is_clear())
         {
            --hare;
         }

         if(hare >= 0 && !tiles_[ords.x][hare].is_clear())
         {
            tiles_[ords.x][tort--].swap(tiles_[ords.x][hare]);
            render();
         }
      }

      fill_col(tile::coords(ords.x, tort));
   }

   /*!
    * \brief Handles the matches described by matches.
    *
    * \param [in,out] matches [in,out] If non-null, the matches.
    */

   void board::handle_matches(std::set<tile *> & matches)
   {
      // a known bug in VS2013 means you can't pass a lambda as a predicate to
      // an STL container unless it captures something. Here we're capturing
      // matches just to stop the false compile time error we'd get otherwise.
      auto sort_pred = [&matches](
                          tile::coords const & L,
                          tile::coords const & R
      ) { return L.x < R.x; };

      // a list of columns to rebuild
      std::set<tile::coords, decltype(sort_pred)> ords(sort_pred);

      // for each match
      for(auto & match : matches)
      {
         // Have we already seen this column?
         // The idea, here, is that we only want to rebuild a column once so
         // if we have more than one match in a column we want to find the one
         // that has the highest row number. We only need rebuilt the row from
         // that point upwards.
         auto && ord = tile::coords(match->get_x(), match->get_y());
         auto itr = ords.find(ord);

         if(itr != ords.end())
         {
            // if we're seen it is this row lower than the previous
            if(itr->y < match->get_y())
            {
               // yes it is, so we'll swap it out.
               ords.erase(itr);
               itr = ords.end();
            }
         }

         // insert the new row for this column
         if(itr == ords.end())
         {
            ords.insert(ord);
         }

         // clear the current match tile (make it blank)
         match->clear();
      }

      render();

      // rebuild the columns for the matches found
      for(auto const & ord : ords)
      {
         rebuild_col(ord);
      }
   }

   /*!
    * \brief Searches for the first matches.
    *
    * \return true if it succeeds, false if it fails.
    */

   bool board::find_matches()
   {
      auto found = false;
      std::set<tile *> matches;

      // scan for matches
      while(scan_for_matches(matches))
      {
         // since one set of matches can create more we re-scan over and over
         // until we find no more mathes
         if(!matches.empty())
         {
            found = true;
            handle_matches(matches);

            // scoring is a simple case of accumulating the matches
            score_ += matches.size();
         }

         // clear this match set in readiness to scan again
         matches.clear();
      }

      return found;
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
         auto this_click = tile::coords ( e.button.x, e.button.y );

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
            if(toggle_tiles(this_click))
            {
               if(!find_matches())
               {
                  toggle_tiles(this_click);
               }

               last_click_ = tile::coords();
            }
         }
         else
         {
            // no tiles selected, unset last click state
            last_click_ = tile::coords();
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
         auto this_click = tile::coords(e.button.x, e.button.y);

         // get the position down to tile granularity
         this_click.x /= tile_size;
         this_click.y /= tile_size;

         // if swipes are allowed
         if(swipe_ok)
         {
            // handle moving tiles
            if(toggle_tiles(this_click))
            {
               if(!find_matches())
               {
                  toggle_tiles(this_click);
               }

               last_click_ = tile::coords();
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

   bool board::toggle_tiles(tile::coords const & this_click)
   {
      bool toggled = false;
      auto & this_tile = tiles_[this_click.x][this_click.y];

      this_tile.selected(true);

      // no previous tile clicked, so just save this click and return
      if(!(last_click_.x < 0 || last_click_.y < 0))
      {
         auto & last_tile = tiles_[last_click_.x][last_click_.y];
         last_tile.selected(false);

         // if this click differs from the last...
         if(this_click != last_click_)
         {

            // get the x/y axis difference between this and last
            auto const x_diff = abs(this_click.x-last_click_.x);
            auto const y_diff = abs(this_click.y-last_click_.y);

            // if this tile is adjacent vertically or horizontally
            if((1 == x_diff && 0 == y_diff) ||
               (0 == x_diff && 1 == y_diff))
            {
               // swap the tiles
               last_tile.swap(this_tile);
               this_tile.selected(false);
               toggled = true;

               // prevent more swiping until mouse unclicked
               swipe_ok = false;
            }
         }
      }

      // render any changes to the board
      render();

      // if we didn't toggle just records this click
      if(!toggled)
      {
         last_click_ = this_click;
      }

      return toggled;
   }
}
