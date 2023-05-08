#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>

#include "entity.h"
#include "component.h"
#include "world.h"
#include "collision.h"

class BounceComponent : public Component {
 public:
  void update(Entity *entity, sf::Time dt, World *world) override {
    Collision collision = world->check_collisions(entity);
    if (std::abs(collision.direction.x) > 0) {
      entity->velocity.x *= -1;
    }
    if (std::abs(collision.direction.y) > 0) {
      entity->velocity.y *= -1;
    }
    // push the entity out of the collision
    entity->x += collision.direction.x * dt.asSeconds() * -1.f;
    entity->y += collision.direction.y * dt.asSeconds() * -1.f;
  }
};
