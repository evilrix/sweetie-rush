/**
 * @file board.cpp
 *
 * @brief Implements the board class.
 */

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
      initialise();

      render();

      SDL_Delay(5000);
   }

   void board::initialise()
   {
      auto && textures = std::vector<std::shared_ptr<texture>>();
      textures.push_back(std::shared_ptr<texture>(new sweetie_blue(ren_)));
      textures.push_back(std::shared_ptr<texture>(new sweetie_green(ren_)));
      textures.push_back(std::shared_ptr<texture>(new sweetie_purple(ren_)));
      textures.push_back(std::shared_ptr<texture>(new sweetie_red(ren_)));
      textures.push_back(std::shared_ptr<texture>(new sweetie_yellow(ren_)));

      SDL_Rect tile_rect {0, 0, tile_size, tile_size};

      for(auto y = 0 ; y < 8 ; ++y)
      {
         tile_rect.x = 0;

         for(auto x = 0 ; x < 8 ; ++x)
         {
            tiles_[x][y] = textures[rand() % textures.size()];
            SDL_RenderCopy(
               ren_.get(), tiles_[x][y]->get(),
               nullptr, &tile_rect);
            tile_rect.x += 36;
         }

         tile_rect.y += 36;
      }
   }

   void board::render() const
   {
      SDL_RenderPresent(ren_.get());
   }
}
