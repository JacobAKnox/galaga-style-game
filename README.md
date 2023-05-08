# galaga-style-game
A Galaga style game base in c++ using SFML. Made for design patterns class in early 2023.

Sprites are from:
https://opengameart.org/content/modular-ships 

Font is Orbitron from:
https://fonts.google.com/specimen/Orbitron

The game can be built using cmake. 

This was developed over the the course of the term as a way to show how various design patterns can be used in a game. 

The config class is a singleton to load config values from config.txt. The first time you call it it will load the values from the passed file, or the default config.txt if no file is passed. Then you can retrive values from the instance.

There is an event manager that makes use of the observer pattern. It can be used to register listeners for events, and then when an event is fired it will notify all listeners.

There a several uses of the factory pattern to create game objects, the player, enemies, and lasers.

All game objects are entities, and the components they have determine their looks and behavior. I would call this a command pattern, but it is blurry. There are a couple specific component types, for visuals and events, but most are generic and can be used for any entity. Each one is updated and has some code that mutates the enemy state, which is the same data for all entities.  

Beyond that there is the menus to start and end the game, and the game loop itself.

## Building and Running
$ cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
$ cmake --build build
$ ./build/CMakeSFMLProject
