#pragma once

#include <SFML/Graphics.hpp>

#include "graphics.h"
#include "graphics_component.h"
#include "entity.h"
#include "world.h"

class BoxGraphicsComponent : public GraphicsComponent {
 private:
  sf::RectangleShape shape;

 public:
  BoxGraphicsComponent(sf::Vector2f size, sf::Color color) {
    shape.setSize(size);
    shape.setFillColor(color);
  }

  void update(const Entity *entity, World *world, Graphics *graphics) override {
    shape.setPosition(entity->x, entity->y);
  }

  void render(Graphics *graphics) override {
    graphics->render(shape);
  }

  void set_color(sf::Color color) override {
    shape.setFillColor(color);
  }

  float get_width() const override {
    return shape.getSize().x;
  }

  float get_height() const override {
    return shape.getSize().y;
  }
};
