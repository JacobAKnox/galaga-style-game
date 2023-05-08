#pragma once

#include <SFML/Graphics.hpp>

#include "box_graphics_component.h"
#include "config.h"
#include "entity.h"
#include "event_component.h"
#include "event_type.h"
#include "laser_collider.h"

constexpr float laser_speed = 300;

class LaserFactory {
 public:
  static Entity *create_laser(Entity *entity, sf::Color color, bool enemy = false) {
    float height = Config::get_instance().get_circle_size() / 2.f;
    float width = height / 8.f;
    sf::Vector2f velocity{0, laser_speed * (enemy ? 1 : -1)};
    sf::Vector2f position{entity->x, entity->y};
    position.y += entity->height * (enemy ? 1 : -1);
    position.x += entity->width / 2.f - width / 2.f;
    EventType type = enemy ? EventType::EnemyLaserHit : EventType::PlayerLaserHit;

    return new Entity{velocity, position, 1, std::make_shared<BoxGraphicsComponent>(sf::Vector2f{width, height}, color),
                      std::make_shared<EventComponent>(), std::make_shared<LaserCollider>(entity->id, type)};
  }
};
