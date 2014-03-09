/** vim: set ft=cpp ts=3 sw=3 tw=0 sts=0 et:
  *
  * @file   : sweetie-rush/game.hpp
  * @author : evilrix
  * @date   : 09/47/2014
  * @brief  : Declares the game class
  *
  */

#pragma once

#include "board.hpp"

namespace sweetie_rush {

   /**
    * @brief A game.
    */

   class game
   {
      public:

         /**
          * @brief Initializes a new instance of the game class.
          */

         game();

      public:

         /**
          * @brief Runs this game.
          */

         void run();

      private:
         board brd_;
   };

}
