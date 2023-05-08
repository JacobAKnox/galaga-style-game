#pragma once

#include <SFML/Graphics.hpp>

#include "entity.h"
#include "component.h"

constexpr float SQUARE_SPEED = 100.0f;
constexpr int TURN_TIME = 40;

class SquareMoveComponent : public Component {
 private:
  void turn(Entity *entity) {
    entity->velocity.y *= -1;
    float temp = entity->velocity.y;
    entity->velocity.y = entity->velocity.x;
    entity->velocity.x = temp;
  }

 public:
  void update(Entity *entity, sf::Time dt, World *world) override {
    if (entity->timer == 0) {
      turn(entity);
      entity->timer = TURN_TIME;
    }
  }
};
