#include <iostream>
#pragma once

class Entity
{
private:
    char symbol;
    int Xposition;
    int Yposition;
    int health;
    int damage;
    int id;
public:
    Entity(int x, int y, int Damage, int Id);
    int get_xposition();
    int get_yposition();
    int get_health();
    int get_damage();
    int get_id();
    void move(int x, int y);
    char get_symbol();
    void take_damage(int amount);
};
