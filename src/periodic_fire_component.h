#pragma once

#include <SFML/Graphics.hpp>

#include "entity.h"
#include "component.h"
#include "rand.h"
#include "laser_factory.h"

constexpr int COOLDOWN = 120;

class PeriodicFireComponent : public Component {
 private:
  int cooldown = 0;

 public:
  PeriodicFireComponent() {
    cooldown = rand_int(0, COOLDOWN);
  }

  void update(Entity *entity, sf::Time dt, World *world) override {
    if (cooldown > 0) {
      cooldown--;
    }
    if (cooldown == 0) {
      world->add_entity(LaserFactory::create_laser(entity,sf::Color::Red, true));
      cooldown = COOLDOWN;
    }
  }
};
