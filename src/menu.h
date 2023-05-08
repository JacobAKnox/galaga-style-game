#pragma once

#include <SFML/Graphics.hpp>

#include "graphics.h"
#include "return_code.h"
#include "menu_display.h"

constexpr int MENU_DELAY = 30;

class Menu {
 protected:
  Graphics *graphics;
  bool running{true};
  int delay{MENU_DELAY};
  MenuDisplay *menu_display;

  void processEvents() {
    sf::Event event;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      graphics->window.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && delay == 0) {
      running = false;
    }
    while (graphics->window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        graphics->window.close();
      }
    }
  }

  void update(sf::Time dt) {
    if (delay > 0) {
      delay--;
    }
    menu_display->update(graphics);
  }

  void render() {
    graphics->window.clear();
    menu_display->render(graphics);
    graphics->window.display();
  }

 public:
  Menu(MenuDisplay *menu_display) {
    this->menu_display = menu_display;
  }

  ReturnCode run_menu(Graphics &graphics) {
    this->graphics = &graphics;
    sf::Clock clock;

    sf::Time t{sf::Time::Zero};
    sf::Time dt{sf::seconds(1.0f / 60.0f)};
    while (graphics.window.isOpen() && running) {
      processEvents();
      t += clock.restart();

      while (t > dt) {
        t -= dt;
        processEvents();
        update(dt);
      }

      render();
    }
    this->graphics = nullptr;
    return !running ? ReturnCode::Continue : ReturnCode::Quit;
  }
};
