#pragma once

#include <vector>
#include <map>
#include <string>
#include "Item.h"
#include "Entity.h"

class Player
{
private:
    char symbol;
    int Xposition;
    int Yposition;
    int health;
    int damage;
    std::vector<Item> inventory;
    std::map<std::string, int> items;
public:
    Player();
    int get_xposition();
    int get_yposition();
    int get_health();
    int get_damage();
    char get_symbol();
    void move(int Xmovement, int Ymovement);
    void combat(Entity enemy);
    void pickup(Item item);
    std::map<std::string, int> get_items();
    std::vector<Item> get_inventory();
    void take_damage(int amount);
};
