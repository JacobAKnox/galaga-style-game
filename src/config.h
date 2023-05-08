#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

/*
    File format:
    any of the following key value pairs can be used in any order
    width: <uint>
    height: <uint>
    enemies: <uint>
    size: <float>
*/

// defining the wrappers for stoul and stof
// compiler cannot deduce the type when using auto for stoul and stof becasue of overrides
// the other option would be to use a lambda on each call, but this is less code
unsigned int stoul(const std::string &s) { return std::stoul(s); }
float stof(const std::string &s) { return std::stof(s); }

class Config {
 public:
  static Config &get_instance(const std::string &filename = "config") {
    static Config instance{filename};
    return instance;
  }

  unsigned int get_width() const { return width; }
  unsigned int get_height() const { return height; }
  unsigned int get_enemy_count() const { return enemy_count; }
  float get_circle_size() const { return size; }
  std::string get_asset_path() const { return asset_path; }

 private:
  static constexpr std::string_view WIDTH_KEY{"width"};
  static constexpr std::string_view HEIGHT_KEY{"height"};
  static constexpr std::string_view ENEMY_COUNT_KEY{"enemies"};
  static constexpr std::string_view CIRCLE_SIZE_KEY{"size"};
  static constexpr std::string_view ASSET_PATH_KEY{"asset_path"};

  static constexpr unsigned int DEFAULT_WIDTH{700};
  static constexpr unsigned int DEFAULT_HEIGHT{600};
  static constexpr unsigned int DEFAULT_ENEMY_COUNT{5};
  static constexpr float DEFAULT_SIZE{22.0f};
  static constexpr std::string_view DEFAULT_ASSET_PATH{"./assets/"};

  Config(std::string_view file) {
    std::unordered_map<std::string, std::string> config = load_config(file);

    size = get_key(config, CIRCLE_SIZE_KEY, stof, size);
    width = get_key(config, WIDTH_KEY, stoul, width);
    height = get_key(config, HEIGHT_KEY, stoul, height);
    enemy_count = get_key(config, ENEMY_COUNT_KEY, stoul, enemy_count);
    asset_path = get_key(config, ASSET_PATH_KEY, [](auto s) { return s; }, asset_path);
  }

  template <typename T>
  T get_key(auto config, std::string_view key, auto conv, T default_value) {
    try {
      // conversion to string is required because unordered_map.at() does not accept herteogeneous keys
      return conv(config.at(std::string{key}));
    } catch (const std::invalid_argument &e) {
      std::cout << "Invalid value for key: " << key << std::endl;
    } catch (const std::out_of_range &e) {
      std::cout << "Could not find value for key: " << key << std::endl;
    }
    std::cout << "Using default value" << std::endl;
    return default_value;
  }

  std::unordered_map<std::string, std::string> load_config(std::string_view file) {
    std::ifstream config_stream{std::string{file}};
    if (!config_stream.is_open()) {
      std::cout << "Error opening config file" << std::endl;
      std::cout << "Using default values" << std::endl;
      return {};
    }
    std::unordered_map<std::string, std::string> config{};
    std::string token{};
    while (std::getline(config_stream, token, ':')) {
      auto key = token;
      std::getline(config_stream, token);
      config[key] = token;
    }
    return config;
  }

  unsigned int enemy_count{DEFAULT_ENEMY_COUNT};
  unsigned int width{DEFAULT_WIDTH};
  unsigned int height{DEFAULT_HEIGHT};
  float size{DEFAULT_SIZE};
  std::string asset_path{DEFAULT_ASSET_PATH};
};
