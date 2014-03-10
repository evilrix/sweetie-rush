/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/board.hpp
  * @author : evilrix
  * @date   : 09/36/2014
  * @brief  : Declares the board class
  *
  */

#pragma once

#include <memory>
#include <array>
#include <vector>

#include "window.hpp"
#include "renderer.hpp"
#include "tile.hpp"

namespace sweetie_rush {

   /**
    * @brief Forward declare texture.
    */

   class texture;

   /**
    * @brief A board.
    */

   class board
   {
      public:

         /**
          * @brief Initializes a new instance of the board class.
          */

         board();

      public:

         /**
          * @brief Initialises this board.
          */

         void initialise();

         /**
          * @brief Renders this board.
          */

         void render() const;

      public:

         /**
          * @brief Handles mouse click signals.
          */

         void on_mouse_click(SDL_Event const & e);

         /**
          * @brief Handles mouse motion signals.
          */

         void on_mouse_motion(SDL_Event const & e);

      private:
         static int const tile_size = tile::dim;
         static int const board_dim = 8;
         static int const board_siz = tile_size * board_dim;

      private:
         using types_t = std::array<std::array<tile, board_dim>, board_dim>;
         using coords = tile::coords;

      private:
         void fill_col(int x, int y);
         bool toggle_tiles(coords const & this_click);
         void clear_xy(coords const & this_click);
         bool clear_x(coords const & this_click);
         bool clear_y(coords const & this_click);
         void handle_drop(tile * pt, tile * pcur);

      private:
         window win_;
         renderer ren_;
         types_t tiles_;
         coords last_click_ = coords {-1, -1};
         bool swipe_ok = true;
         std::vector<std::shared_ptr<sweetie>> sweets_;
   };

}
