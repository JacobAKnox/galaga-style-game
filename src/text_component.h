#pragma once

#include <SFML/Graphics.hpp>

#include "graphics_component.h"
#include "entity.h"
#include "world.h"
#include "graphics.h"
#include "files.h"

class TextComponent : public GraphicsComponent {
 private:
  sf::Text text;
  sf::Font font;

 public:
  TextComponent(std::string text, std::string font_name, float size, sf::Color color) : text{}, font{} {
    load_font(font, font_name);
    this->text = sf::Text{text, font, (unsigned int) size};
    this->text.setFillColor(color);
  }

  void update(const Entity *entity, World *world, Graphics *graphics) override {
    text.setPosition(entity->x, entity->y);
  }

  void render(Graphics *graphics) override {
    graphics->render(text);
  }

  void set_color(sf::Color color) override {
   text.setFillColor(color);
  }

  void set_text(std::string text) {
    this->text.setString(text);
  }

  float get_width() const override {
    return text.getGlobalBounds().width;
  }

  float get_height() const override {
    return text.getGlobalBounds().height;
  }
};
