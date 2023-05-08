#include <SFML/Graphics.hpp>

#include "config.h"
#include "enemy_factory.h"
#include "graphics.h"
#include "player_factory.h"
#include "rand.h"
#include "stop_component.h"
#include "world.h"
#include "return_code.h"
#include "game_manager_factory.h"
#include "menu_factories.h"
#include "menu_display.h"
#include "menu.h"

ReturnCode run_game(Graphics &graphics) {
  auto config = Config::get_instance();

  auto width = config.get_width();
  auto height = config.get_height();
  auto size = config.get_circle_size();
  auto enemy_count = config.get_enemy_count();

  World world{&graphics};

  world.add_player(PlayerFactory::create_player(size, width, height));
  world.add_entity(GameManagerFactory::create_game_manager());
  EnemyFactory::create_enemies(world, enemy_count, size, width, height);

  return world.run();
}

ReturnCode run_menu(Graphics &graphics, MenuDisplay *menu_display) {
  Menu menu{menu_display};
  return menu.run_menu(graphics);
}

int main(int argc, char *argv[]) {
  if (argc > 1) {
    Config::get_instance(argv[1]);
  } else {
    std::cout << "No config file specified, attempting to use defualt config file" << std::endl;
    Config::get_instance();  // access default config file defaulted in config.h
  }

  auto config = Config::get_instance();

  auto width = config.get_width();
  auto height = config.get_height();

  Graphics graphics{width, height};

  ReturnCode return_code{ReturnCode::Continue};

  MenuDisplay start_menu = MenuFactory::create_start_menu();
  MenuDisplay win_menu = MenuFactory::create_win_menu();
  MenuDisplay lose_menu = MenuFactory::create_lose_menu();

  while (return_code == ReturnCode::Continue) {
    return_code = run_menu(graphics, &start_menu);
    if (return_code == ReturnCode::Continue) {
      return_code = run_game(graphics);
    }
    return_code = run_menu(graphics, return_code == ReturnCode::Win ? &win_menu : &lose_menu);
  }
}
