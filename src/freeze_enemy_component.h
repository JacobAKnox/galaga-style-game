#pragma once

#include <SFML/Graphics.hpp>

#include "entity.h"
#include "event_component.h"

constexpr int FREEZE_TIME = 40;

class FreezeComponent : public EventComponent {
 private:
  bool frozen = false;
  sf::Vector2f old_velocity;

 public:
  void update(Entity *entity, sf::Time dt, World *world) override {
    if (frozen && entity->timer == 0) {
      frozen = false;
      entity->set_velocity(old_velocity);
    }
  }

  void handle_event(Entity *entity, EventType event) override {
    if (event == EventType::Flash) {
      if (frozen) {
        return;
      }

      frozen = true;
      old_velocity = entity->velocity;
      entity->set_velocity(sf::Vector2f{0.0, 0.0});
      entity->timer = FREEZE_TIME;
    }
    if (event == EventType::PlayerLaserHit) {
      entity->health--;
    }
  }
};
