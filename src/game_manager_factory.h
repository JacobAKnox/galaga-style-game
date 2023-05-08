#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "component.h"
#include "entity.h"
#include "event_component.h"
#include "game_manager_component.h"
#include "player_ui_component.h"
#include "text_component.h"

class GameManagerFactory {
 public:
  static Entity *create_game_manager() {
    sf::Vector2f position{0.f, 0.f};
    sf::Vector2f velcoity{0.f, 0.f};
    std::shared_ptr<EventComponent> event_component = std::make_shared<EventComponent>();
    std::shared_ptr<GameManagerComponent> game_manager = std::make_shared<GameManagerComponent>();
    std::shared_ptr<PlayerUiComponent> player_ui = std::make_shared<PlayerUiComponent>();
    return new Entity(velcoity, position, 1, player_ui, event_component, game_manager);
  }
};
