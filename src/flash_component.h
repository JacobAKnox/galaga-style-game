#pragma once

#include <SFML/Graphics.hpp>

#include "component.h"
#include "entity.h"

constexpr int FLASH_DURATION = 50;

class FlashComponent : public Component {
 public:
  void update(Entity *entity, sf::Time dt, World *world) override {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && entity->timer == 0) {
      entity->timer = FLASH_DURATION;
      EventManager::get_instance().notify(Flash);
      entity->set_color(sf::Color::Red);
    }

    if (entity->timer == 0) {
      entity->set_color(sf::Color::White);
    }
  }
};
