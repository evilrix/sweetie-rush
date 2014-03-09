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
         void on_mouse_click();

      private:
         static int const tile_size = tile::dim;
         static int const board_dim = 8;
         static int const board_siz = tile_size * board_dim;

      private:
         using types_t = std::array<std::array<tile, board_dim>, board_dim>;

      private:
         window win_;
         renderer ren_;
         types_t tiles_;
   };

}
