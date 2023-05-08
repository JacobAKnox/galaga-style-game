#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "entity.h"
#include "component.h"

constexpr float MAX_SPEED = 300;

class AccelerationMoveComponent : public Component {
 public:
  void update(Entity *entity, sf::Time dt, World *world) override {
    entity->velocity.x += entity->acceleration.x * dt.asSeconds();
    entity->velocity.y += entity->acceleration.y * dt.asSeconds();

    float speed = hypot(entity->velocity.x, entity->velocity.y);
    if (speed > MAX_SPEED) {
      entity->velocity.x = entity->velocity.x * (MAX_SPEED / speed);
      entity->velocity.y = entity->velocity.y * (MAX_SPEED / speed);
    }
  }
};
