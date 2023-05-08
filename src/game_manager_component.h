#pragma once

#include <SFML/Graphics.hpp>

#include "entity.h"
#include "component.h"
#include "world.h"
#include "return_code.h"

class GameManagerComponent : public Component {
 public:
  void update(Entity *entity, sf::Time dt, World *world) override {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      world->return_code = ReturnCode::Quit;
      return;
    }
    if (world->player == nullptr) {
      world->return_code = ReturnCode::Lose;
      return;
    }
    if (world->get_entity_count() == 2) { // player and game manager
      world->return_code = ReturnCode::Win;
      return;
    }
  }
};
