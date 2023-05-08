#pragma once

#include <SFML/Graphics.hpp>

#include "event_type.h"
#include "component.h"

class Entity;

class EventComponent : public Component {
 public:
  virtual ~EventComponent() = default;
  virtual void update(Entity *entity, sf::Time dt, World *world) {};
  virtual void handle_event(Entity *entity, EventType event) {};
};
