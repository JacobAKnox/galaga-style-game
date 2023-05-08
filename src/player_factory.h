#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "acceleration_move_component.h"
#include "config.h"
#include "entity.h"
#include "event_component.h"
#include "flash_component.h"
#include "player_input_component.h"
#include "rand.h"
#include "stop_component.h"
#include "texture_component.h"
#include "fire_component.h"

class PlayerFactory {
 public:
  static Entity *create_player(float size, int width, int height) {
    sf::Vector2f velocity{0, 0};
    sf::Vector2f position{width / 2.f, height / 4.f * 3.f};
    return new Entity{velocity, position, 3, std::make_shared<TextureComponent>("player.png", size), std::make_shared<EventComponent>(),
                      std::make_shared<PlayerInputComponent>(), std::make_shared<AccelerationMoveComponent>(), std::make_shared<StopComponent>(),
                      std::make_shared<FlashComponent>(), std::make_shared<FireComponent>()};
  }
};
