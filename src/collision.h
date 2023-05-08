#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>

#include "entity.h"

bool same_sign(float a, float b) {
  return a*b > 0.f;
}

class Collision {
 public:
  sf::Vector2f direction;
  std::vector<Entity *> colliding_with;

  Collision(sf::Vector2f direction, std::vector<Entity *> &collisions) : direction{direction}, colliding_with{collisions} {}
  Collision() = default;

  static Collision merge(const Collision &c1, const Collision &c2) {
    sf::Vector2f collision_direction = combine_directions(c1.direction, c2.direction);
    std::vector<Entity *> collisions = c1.colliding_with;
    collisions.insert(collisions.end(), c2.colliding_with.begin(), c2.colliding_with.end());
    return Collision{collision_direction, collisions};
  }

  static sf::Vector2f combine_directions(sf::Vector2f a, sf::Vector2f b) {
    sf::Vector2f collision_direction{};
    if (same_sign(a.x, b.x)) {
      collision_direction.x = std::abs(a.x) > std::abs(b.x) ? a.x : b.x;
    } else {
      collision_direction.x = a.x + b.x;
    }

    if (same_sign(a.y, b.y)) {
      collision_direction.y = std::abs(a.y) > std::abs(b.y) ? a.y : b.y;
    } else {
      collision_direction.y = a.y + b.y;
    }
    return collision_direction;
  }
};
