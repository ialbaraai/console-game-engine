#pragma once

#include <vector>
#include <map>
#include <string>

#include "Player.h"
#include "Entity.h"
#include "Item.h"

class Game
{
private:
    bool IS_COMBAT;
    bool IS_COLLIDE;
    bool IS_END;
    bool IS_RUNNING;
    std::vector<std::string> map = {};
    int map_lines;
    Player currentPlayer;
    std::vector<Entity> currentEntities = {};
    int currentEntitiesAmount;
    std::vector<Item> currentItems = {};
    int currentItemsAmount;
    bool is_combat;
public:
    Game(const std::string& filepath, Player *player, std::vector<Entity> *entities, std::vector<Item> *items, bool combat, bool collide, bool end);
    void clear_screen();
    void run();
    void load_map(std::string filename);
    void render();
    char process_input();
    void update();
    bool move_player(int x, int y);
    void move_entities();
    void check_collision();
    void handle_combat(Entity *entity);
    void is_game_over();
};
