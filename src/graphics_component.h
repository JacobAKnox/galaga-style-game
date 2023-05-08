#pragma once

#include <SFML/Graphics.hpp>

class Entity;

#include "graphics.h"

class GraphicsComponent {
 public:
  virtual ~GraphicsComponent() = default;
  virtual void update(const Entity *entity, World *world, Graphics *graphics) = 0;
  virtual void render(Graphics *graphics) = 0;
  virtual void set_color(sf::Color color) = 0;
  virtual float get_width() const = 0;
  virtual float get_height() const = 0;
};
