#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "config.h"
#include "files.h"
#include "graphics.h"

class MenuDisplay {
 private:
  sf::Text title;
  sf::Text flashing_line;
  std::vector<sf::Text> texts{};
  sf::Font font;
  int timer;
  int period;

 public:
  template <typename... Ss>
  MenuDisplay(std::string title, std::string flashing_line, int period, Ss... lines) : timer{period}, period{period} {
    load_font(font, "Orbitron.ttf");
    auto config = Config::get_instance();
    unsigned int title_size = (unsigned int)config.get_circle_size() * 2;
    unsigned int line_size = (unsigned int)config.get_circle_size() * 1;
    int width = config.get_width();
    int height = config.get_height();

    this->title = sf::Text{title, font, title_size};
    auto center = this->title.getGlobalBounds().getSize() / 2.f;
    auto local_center = center + (this->title.getLocalBounds().getPosition());
    this->title.setOrigin(local_center);
    this->title.setPosition(width / 2.f, height * (1.f / 3.f));
    // dark green
    this->title.setFillColor(sf::Color{0, 100, 0});

    this->flashing_line = sf::Text{flashing_line, font, line_size};
    this->flashing_line.setOrigin(this->flashing_line.getGlobalBounds().width / 2.f, 0);
    this->flashing_line.setPosition(this->title.getPosition().x, this->title.getPosition().y + this->title.getGlobalBounds().height + 10);
    this->flashing_line.setFillColor(sf::Color::Transparent);

    float y = this->flashing_line.getPosition().y + this->flashing_line.getGlobalBounds().height + 10;

    for (std::string line : {lines...}) {
      sf::Text text{line, font, line_size};
      text.setOrigin(text.getGlobalBounds().width / 2.f, 0);
      text.setPosition(this->title.getPosition().x, y);
      y += text.getGlobalBounds().height + 10;
      // blue
      text.setFillColor(sf::Color{0, 0, 255});
      this->texts.push_back(text);
    }
  }

  void update(Graphics *graphics) {
    if (timer == 0 && period != 0) {
      flashing_line.setFillColor(flashing_line.getFillColor() == sf::Color::Transparent ? sf::Color::White : sf::Color::Transparent);
      timer = period;
    } else {
      timer--;
    }
  }

  void render(Graphics *graphics) {
    graphics->render(title);
    graphics->render(flashing_line);
    for (auto text : texts) {
      graphics->render(text);
    }
  }
};
