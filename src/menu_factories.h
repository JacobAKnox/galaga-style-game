#pragma once

#include <SFML/Graphics.hpp>

#include "menu_display.h"

class MenuFactory {
 public:
  static MenuDisplay create_start_menu() {
    return MenuDisplay("Game!", "Press space to start", 30, "Arrow Keys: Move", "Z: Taunt", "X: Shoot", "Escape: Quit");
  }

  static MenuDisplay create_lose_menu() {
    return MenuDisplay("You lose!", "Press space to continue", 30, "");
  }

  static MenuDisplay create_win_menu() {
    return MenuDisplay("You win!", "Press space to continue", 30, "");
  }
};
