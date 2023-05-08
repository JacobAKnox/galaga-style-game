#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class World;

#include "component.h"
#include "event_component.h"
#include "event_manager.h"
#include "graphics_component.h"
#include "listener.h"

class Entity : public Listener {
 public:
  // Event and graphics need to be handled differently because so they are separate pointers
  std::shared_ptr<EventComponent> event_component;
  std::shared_ptr<GraphicsComponent> graphics_component;
  std::vector<std::shared_ptr<Component>> components{};

  sf::Vector2f velocity{};
  sf::Vector2f acceleration{};
  float x{};
  float y{};
  float width{};
  float height{};
  int timer{};

  unsigned int health{1};

  int id{-1};

  Entity() = default;

  template <typename... Cs>
  Entity(sf::Vector2f velocity, sf::Vector2f position, unsigned int health, std::shared_ptr<GraphicsComponent> graphics, std::shared_ptr<EventComponent> event, Cs... components)
      : velocity{velocity}, x{position.x}, y{position.y}, health{health}, event_component{event}, graphics_component{graphics} {
    // compiler cannot deduce type if i do:
    // for (std::shared_ptr<Component> component : {component...})
    std::vector<std::shared_ptr<Component>> c{components...};
    for (std::shared_ptr<Component> component : c) {
      this->components.push_back(component);
    }

    this->components.push_back(event_component);
    width = graphics_component->get_width();
    height = graphics_component->get_height();
  }

  virtual void update(sf::Time dt, Graphics *graphics, World *world) {
    if (timer > 0) {
      timer--;
    }
    for (auto &component : components) {
      component->update(this, dt, world);
    }
    x += velocity.x * dt.asSeconds();
    y += velocity.y * dt.asSeconds();
  }

  void render(Graphics *graphics, World *world) const {
    graphics_component->update(this, world, graphics);
    graphics_component->render(graphics);
  }

  void set_color(sf::Color color) {
    graphics_component->set_color(color);
  }

  sf::Vector2f get_velocity() const {
    return velocity;
  }

  void set_velocity(sf::Vector2f velocity) {
    this->velocity = velocity;
  }

  void set_timer(int timer) {
    this->timer = timer;
  }

  int get_timer() const {
    return timer;
  }

  void add_component(std::shared_ptr<Component> component) {
    components.push_back(component);
  }

  void on_event(EventType type) {
    event_component->handle_event(this, type);
  }
};
