#pragma once

#include <SFML/Graphics.hpp>

#include "collision.h"
#include "component.h"
#include "entity.h"
#include "world.h"

constexpr unsigned int IFRAMES = 30;

class StopComponent : public Component {
 private:
  unsigned int iframes = 0;

 public:
  void update(Entity *entity, sf::Time dt, World *world) override {
    Collision collision;

    if (iframes > 0) {
      iframes--;
      collision = world->check_wall_collision(entity);
    } else {
      collision = world->check_collisions(entity);
    }

    if (collision.direction.x < 0 && entity->velocity.x < 0) {
      entity->velocity.x = 0;
    }
    if (collision.direction.x > 0 && entity->velocity.x > 0) {
      entity->velocity.x = 0;
    }
    if (collision.direction.y < 0 && entity->velocity.y < 0) {
      entity->velocity.y = 0;
    }
    if (collision.direction.y > 0 && entity->velocity.y > 0) {
      entity->velocity.y = 0;
    }
    // push the entity out of the collision
    entity->x += collision.direction.x * dt.asSeconds() * -1.f;
    entity->y += collision.direction.y * dt.asSeconds() * -1.f;

    if (collision.colliding_with.size() > 0) {
      iframes = IFRAMES;
      entity->health--;
      entity->on_event(EventType::EntityCollision);
    }
  }
};
