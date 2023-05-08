#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "component.h"
#include "entity.h"

constexpr float ACCELERATION = 1000;
constexpr float DRAG = 500;

class PlayerInputComponent : public Component {
 public:
  void update(Entity *entity, sf::Time dt, World *world) override {
    entity->acceleration.x = 0;
    entity->acceleration.y = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      entity->acceleration.x += -ACCELERATION;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      entity->acceleration.x += ACCELERATION;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      entity->acceleration.y += -ACCELERATION;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      entity->acceleration.y += ACCELERATION;
    }

    // apply some drag to the player
    if (entity->acceleration == sf::Vector2f{0, 0}) {
      sf::Vector2f temp = entity->velocity;
      float speed = hypot(temp.x, temp.y);
      if (speed > 0.1) {
        temp.x = -temp.x * DRAG / speed;
        temp.y = -temp.y * DRAG / speed;
        entity->acceleration = temp;
      } else {
        entity->velocity = sf::Vector2f{0, 0};
      }
    }
  }
};
