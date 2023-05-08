#pragma once

#include <SFML/Graphics.hpp>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <vector>

#include "collision.h"
#include "entity.h"
#include "graphics.h"
#include "return_code.h"

constexpr int MOVE_SPEED = 100;

class World {
 private:
  std::unordered_map<int, Entity *> entities{};
  std::queue<Entity *> add_queue{};
  Graphics *graphics;

  int next_id{0};

  void processEvents() {
    sf::Event event;
    while (graphics->window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        graphics->window.close();
      }
    }
  }

  void update(sf::Time dt) {
    for (auto &entity : entities) {
      entity.second->update(dt, graphics, this);
    }
  }

  void add_queued_entities() {
    while (!add_queue.empty()) {
      entities[next_id] = add_queue.front();
      add_queue.front()->id = next_id;
      add_queue.pop();
      next_id++;
    }
  }

  void remove_entities() {
    auto out = std::ranges::views::filter(entities, [this](const auto &entity) {
      if (entity.second->health <= 0) {
        if (player != nullptr && entity.second->id == player->id) {
          player = nullptr;
        }
        EventManager::get_instance().remove_listener(entity.second);
        delete entity.second;
        return false;
      }
      return true;
    });
    entities = std::unordered_map<int, Entity *>{out.begin(), out.end()};
  }

  void draw() {
    for (auto &entity : entities) {
      entity.second->render(graphics, this);
    }
  }

  void render() {
    // always clear!
    graphics->window.clear();

    draw();

    // swap the display buffer (double-buffering)
    graphics->window.display();
  }

 public:
  Entity *player;
  ReturnCode return_code{ReturnCode::Continue};

  World(Graphics *graphics_ptr) : graphics{graphics_ptr} {}

  ~World() {
    for (auto &entity : entities) {
      delete entity.second;
    }
  }

  ReturnCode run() {
    sf::Clock clock;

    sf::Time t{sf::Time::Zero};              // time
    sf::Time dt{sf::seconds(1.0f / 60.0f)};  // delta time (fixed to 60fps)

    while (graphics->window.isOpen() && return_code == ReturnCode::Continue) {
      add_queued_entities();
      remove_entities();
      processEvents();
      t += clock.restart();

      while (t > dt) {
        t -= dt;
        processEvents();
        update(dt);
      }

      render();
    }
    return return_code;
  }

  int get_width() {
    return graphics->window.getSize().x;
  }

  int get_height() {
    return graphics->window.getSize().y;
  }

  void add_entity(Entity *entity) {
    add_queue.push(entity);
  }

  void add_player(Entity *ship) {
    player = ship;
    add_entity(ship);
  }

  size_t get_entity_count() {
    return entities.size();
  }

  Collision check_entity_collisions(Entity *entity) {
    sf::Vector2f direction{};
    std::vector<Entity *> collisions{};
    for (auto &e : entities) {
      if (e.first == entity->id) {
        continue;
      }
      sf::Vector2f check = check_collision(entity, e.second);
      if (check.x != 0 || check.y != 0) {
        direction = Collision::combine_directions(direction, check);
        collisions.push_back(e.second);
      }
    }
    return Collision{direction, collisions};
  }

  Collision check_wall_collision(Entity *entity) {
    sf::Vector2f collision{};
    if (entity->x < 0) {
      collision.x += entity->x;
    }
    if (entity->x + entity->width > get_width()) {
      collision.x += entity->x + entity->width - get_width();
    }
    if (entity->y < 0) {
      collision.y += entity->y;
    }
    if (entity->y + entity->height > get_height()) {
      collision.y += entity->y + entity->height - get_height();
    }
    std::vector<Entity *> _{};
    return Collision{collision, _};
  }

  Collision check_collisions(Entity *entity) {
    return Collision::merge(check_wall_collision(entity), check_entity_collisions(entity));
  }

  sf::Vector2f check_collision(Entity *entity1, Entity *entity2) {
    sf::Vector2f entity1_1{entity1->x, entity1->y}, entity1_2{entity1->x + entity1->width, entity1->y + entity1->height};
    sf::Vector2f entity2_1{entity2->x, entity2->y}, entity2_2{entity2->x + entity2->width, entity2->y + entity2->height};
    sf::Vector2f collision{};
    // vertical collision
    if (entity1_1.x < entity2_2.x && entity1_2.x > entity2_1.x) {
      if (entity1_1.y < entity2_1.y && entity1_2.y > entity2_1.y) {
        collision.y += entity1_2.y - entity2_1.y;
      }
      if (entity1_1.y < entity2_2.y && entity1_2.y > entity2_2.y) {
        collision.y += entity1_1.y - entity2_2.y;
      }
    }

    // horizontal collision
    if (entity1_1.y < entity2_2.y && entity1_2.y > entity2_1.y) {
      if (entity1_1.x < entity2_1.x && entity1_2.x > entity2_1.x) {
        collision.x += entity1_2.x - entity2_1.x;
      }
      if (entity1_1.x < entity2_2.x && entity1_2.x > entity2_2.x) {
        collision.x += entity1_1.x - entity2_2.x;
      }
    }

    return collision;
  }
};
