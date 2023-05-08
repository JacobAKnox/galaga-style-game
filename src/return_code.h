#pragma once

enum class ReturnCode {
  Continue, // go to next menu/start the game
  Win, // the player won
  Lose, // the player lost
  Quit // quit the game, close the window
};
