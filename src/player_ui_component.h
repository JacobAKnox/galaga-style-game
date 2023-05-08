#pragma once

#include <SFML/Graphics.hpp>

#include "config.h"
#include "entity.h"
#include "files.h"
#include "graphics.h"
#include "graphics_component.h"
#include "world.h"

// do nothing for now, will add health display later
class PlayerUiComponent : public GraphicsComponent {
 private:
  sf::Texture texture;
  sf::RectangleShape sprite{};
  float width{};
  float height{};

 public:
  PlayerUiComponent() {
    load_texture(texture, "player.png");
    texture.setSmooth(true);
    texture.setRepeated(true);
    sprite.setTexture(&texture, true);
    height = Config::get_instance().get_circle_size() / 2;
    width = height * 3;
    sprite.setSize(sf::Vector2f{width, height});
    sprite.setTextureRect(sf::IntRect{0, 0, (int)texture.getSize().x * 3, (int)texture.getSize().y});
    sprite.setPosition(0, 0);
  }

  void update(const Entity *entity, World *world, Graphics *graphics) override {
    int health = 0;
    if (world->player != nullptr) {
      health = world->player->health;
    }
    width = height * health;
    sprite.setSize(sf::Vector2f{width, height});
    sprite.setTextureRect(sf::IntRect{0, 0, (int)texture.getSize().x * health, (int)texture.getSize().y});
  }

  void render(Graphics *graphics) override {
    graphics->render(sprite);
  }

  void set_color(sf::Color color) override {}

  float get_width() const override {
    return 0.f;
  }

  float get_height() const override {
    return 0.f;
  }
};
