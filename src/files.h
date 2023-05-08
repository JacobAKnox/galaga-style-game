#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>

#include "config.h"

namespace fs = std::filesystem;

void load_texture(sf::Texture &texture, const std::string_view texture_name) {
  fs::path path = fs::current_path().append(Config::get_instance().get_asset_path()).append(texture_name);
  if (!texture.loadFromFile(path.string())) {
    throw std::runtime_error("Could not load texture");
  }
}

void load_font(sf::Font &font, const std::string_view font_name) {
  fs::path path = fs::current_path().append(Config::get_instance().get_asset_path()).append(font_name);
  if (!font.loadFromFile(path.string())) {
    throw std::runtime_error("Could not load font");
  }
}
