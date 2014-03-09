/**
 * @file board.hpp
 *
 * @brief Declares the board class.
 */

#pragma once

#include <memory>
#include <array>

#include "window.hpp"
#include "renderer.hpp"

namespace sweetie_rush {

   class texture;

   class board
   {
      public:
         board();

      public:
         void initialise();
         void render() const;

      private:
         static int const tile_size = 36;
         static int const board_dim = 8;
         static int const board_siz = tile_size * board_dim;

      private:
         using types_t = std::array<std::array<
                         std::shared_ptr<texture>, board_dim>, board_dim>;

      private:
         window win_;
         renderer ren_;
         types_t tiles_;
   };

}
