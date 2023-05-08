#pragma once

#include <random>

float rand_float(float min, float max) {
  static std::random_device rd{};
  static std::mt19937 gen{rd()};

  std::uniform_real_distribution<float> distrib{min, max};
  return distrib(gen);
}

int rand_int(int min, int max) {
  static std::random_device rd{};
  static std::mt19937 gen{rd()};

  std::uniform_int_distribution<int> distrib{min, max};
  return distrib(gen);
}

sf::Vector2f rand_vec2(float min, float max) {
  return sf::Vector2f{rand_float(min, max), rand_float(min, max)};
}

sf::Vector2f rand_vec2(float x_min, float x_max, float y_min, float y_max) {
  return sf::Vector2f{rand_float(x_min, x_max), rand_float(y_min, y_max)};
}
