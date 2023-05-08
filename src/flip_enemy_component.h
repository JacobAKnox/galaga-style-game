#pragma once

#include <SFML/Graphics.hpp>

#include "entity.h"
#include "event_component.h"

class FlipComponent : public EventComponent {
 public:
  void update(Entity *entity, sf::Time dt, World *world) override {
    // nothing to do on update
  }

  void handle_event(Entity *entity, EventType event) override {
    if (event == EventType::Flash) {
      entity->velocity.x *= -1;
      entity->velocity.y *= -1;
    }
    if (event == EventType::PlayerLaserHit) {
      entity->health--;
    }
  }
};
