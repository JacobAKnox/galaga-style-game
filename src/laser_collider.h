#pragma once

#include <SFML/Graphics.hpp>

#include "collision.h"
#include "component.h"
#include "entity.h"
#include "event_type.h"
#include "world.h"

class LaserCollider : public Component {
  private:
    unsigned int fired_by;
    EventType laser_type;
 public:
  LaserCollider(unsigned int fired_from, EventType laser_type) : fired_by{fired_from}, laser_type{laser_type} {}

  void update(Entity *entity, sf::Time dt, World *world) override {
    Collision collision = world->check_collisions(entity);
    if (collision.direction != sf::Vector2f(0, 0)) {
      entity->health = 0;
    }
    for (auto entity : collision.colliding_with) {
      if (entity->id == fired_by) {
        continue;
      }
      entity->on_event(laser_type);
    }
  }
};
