#pragma once

#include <SFML/Graphics.hpp>

class Graphics {
public:
  sf::RenderWindow window;

  Graphics(unsigned int width, unsigned int height): window(sf::VideoMode(width, height), "Game") {}

  void render(sf::Drawable &drawable) {
    window.draw(drawable);
  }
};
