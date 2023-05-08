#pragma once

#include <SFML/Graphics.hpp>

#include "component.h"
#include "entity.h"
#include "laser_factory.h"
#include "world.h"

constexpr int fire_cooldown = 10;

class FireComponent : public Component {
 private:
  int timer = 0;
 public:
  void update(Entity *entity, sf::Time dt, World *world) override {
    if (timer > 0) {
      timer--;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && timer == 0) {
      world->add_entity(LaserFactory::create_laser(entity, sf::Color::Green));
      timer = fire_cooldown;
    }
  }
};
