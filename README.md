# Console Game Engine

A simple, console-based game engine written in C++17, built entirely without external libraries.

## Features
 - ASCII map loading from `.txt` files in `assets/` directory
 - Player movement with WASD, wall collision, and bounds checking
 - Monster Ai with basic pathfinding toward the player
 - Turn-based combat with HP tracking
 - Item pickup and invetory system

## Dependencies
 - C++17 Standard Library (`vector`, `map`, `string`, `fstream`, `iostream`)

## Building
```bash
cmake -S . -B build
cd build
make
./game
```

## Usage
Place your map as a `.txt` file inside the `assets/` director, then intialize and run the game:
```cpp
Game game(const std::string& Your_Map_Filepath, Player *Your_Player, std::vector<Entity> *Your_Entities_Vector, std::vector<Item> *Your_Items_Vector, bool combat, bool collide, bool end);
game.run();
```
---

## License

This project is licensed under the MIT License. See [LICENSE](./LICENSE) for details.

---

## Author

**albaraa** — [@ialbaraai](https://github.com/ialbaraai)