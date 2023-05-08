#pragma once

#include <SFML/Graphics.hpp>

class World;
class Entity;

class Component {
 public:
  virtual ~Component() = default;
  virtual void update(Entity *entity, sf::Time dt, World *world) {};
};
