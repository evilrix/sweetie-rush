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
#include <set>

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

         /*!
          * \brief Renders the given pause.
          *
          * \param pause (Optional) the pause.
          */

         void render(bool const delay = true) const;

      public:

         /**
          * @brief Handles mouse click signals.
          */

         void on_mouse_click(SDL_Event const & e);

         /**
          * @brief Handles mouse motion signals.
          */

         void on_mouse_motion(SDL_Event const & e);

         /*!
          * \brief Gets the score.
          *
          * \return The score.
          */

         size_t get_score() const { return score_; }


      private:

         /*!
          * \brief Fill col.
          *
          * \param ords    The ords.
          * \param animate (Optional) the animate.
          */

         void fill_col(tile::coords const & ords, bool const animate = true);

         /*!
          * \brief Rebuild col.
          *
          * \param ords The ords.
          */

         void rebuild_col(tile::coords const & ords);

         /*!
          * \brief Toggle tiles.
          *
          * \param this_click this click.
          *
          * \return true if it succeeds, false if it fails.
          */

         bool toggle_tiles(tile::coords const & this_click);

         /*!
          * \brief Searches for the first matches.
          *
          * \return true if it succeeds, false if it fails.
          */

         bool find_matches();

         /*!
          * \brief Scans for matches.
          *
          * \param [in,out] matches [in,out] If non-null, the matches.
          *
          * \return true if it succeeds, false if it fails.
          */

         bool scan_for_matches(std::set<tile *> & matches);

         /*!
          * \brief Handles the matches described by matches.
          *
          * \param [in,out] matches [in,out] If non-null, the matches.
          */

         void handle_matches(std::set<tile *> & matches);

      private:
         static int const tile_size = tile::dim;
         static int const board_dim = 8;
         static int const board_siz = tile_size * board_dim;
         using types_t = std::array<std::array<tile, board_dim>, board_dim>;

      private:
         window win_;
         renderer ren_;
         types_t tiles_;
         tile::coords last_click_;
         bool swipe_ok = true;
         std::vector<std::shared_ptr<sweetie>> sweets_;
         size_t score_ = 0;
   };

}
