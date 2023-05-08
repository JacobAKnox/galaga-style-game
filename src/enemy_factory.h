#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

#include "acceleration_move_component.h"
#include "bounce_component.h"
#include "entity.h"
#include "event_manager.h"
#include "flip_enemy_component.h"
#include "freeze_enemy_component.h"
#include "periodic_fire_component.h"
#include "rand.h"
#include "square_move_component.h"
#include "texture_component.h"
#include "world.h"

class EnemyFactory {
 public:
  static Entity* create_enemy(float size, int width, int height) {
    sf::Vector2f pos = rand_vec2(size, width - 10.f * size, size + 10.f, height / 2.f);
    sf::Vector2f velocity = rand_vec2(-100.f, 100.f);

    // assign a random texture
    std::string texture = rand_float(0, 2) > 1 ? "enemy1.png" : "enemy2.png";
    std::shared_ptr<GraphicsComponent> graphics_component = std::make_shared<TextureComponent>(texture, size);

    std::shared_ptr<EventComponent> event_component;
    std::shared_ptr<Component> collider = std::make_shared<BounceComponent>();
    std::shared_ptr<Component> fire_component = std::make_shared<PeriodicFireComponent>();
    std::shared_ptr<Component> component;
    if (rand_float(0, 2) > 1) {
      event_component = std::make_shared<FreezeComponent>();
      component = std::make_shared<SquareMoveComponent>();
      velocity = {SQUARE_SPEED, 0};
    } else {
      event_component = std::make_shared<FlipComponent>();
    }
    Entity* enemy = new Entity{velocity, pos, 2, graphics_component, event_component, collider, fire_component};
    if (component) {
      enemy->add_component(component);
    }
    EventManager::get_instance().add_listener(enemy, Flash);
    return enemy;
  }

  static void create_enemies(World& world, int count, float size, int width, int height) {
    for (int i{}; i < count; ++i) {
      world.add_entity(create_enemy(size, width, height));
    }
  }
};
