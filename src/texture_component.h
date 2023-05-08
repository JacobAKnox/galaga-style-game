#pragma once

#include <SFML/Graphics.hpp>

#include "graphics_component.h"
#include "config.h"
#include "entity.h"
#include "graphics.h"
#include "files.h"

class TextureComponent : public GraphicsComponent {
 private:
  sf::Sprite sprite;
  sf::Texture texture;

 public:
  TextureComponent(std::string texture_name, float size) : sprite{}, texture{} {
    load_texture(texture, texture_name);
    // smooth is false becasue it looks better for pixel art
    texture.setSmooth(false);
    sprite = sf::Sprite{texture};
    float scale = size / sprite.getGlobalBounds().height;
    sprite.setScale(scale, scale);
  }

  void update(const Entity *entity, World *world, Graphics *graphics) override {
    sprite.setPosition(entity->x, entity->y);
  }

  void render(Graphics *graphics) override {
    graphics->render(sprite);
  }

  void set_color(sf::Color color) override {
   sprite.setColor(color);
  }

  float get_width() const override {
    return sprite.getGlobalBounds().width;
  }

  float get_height() const override {
    return sprite.getGlobalBounds().height;
  }
};
