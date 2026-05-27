#pragma once

#include <string>

class Item
{
private:
    char symbol;
    std::string name;
    int Xposition;
    int Yposition;
    int Damage;
public:
    Item(std::string Name, int xposition, int yposition, int damage);
    int get_xposition();
    int get_yposition();
    char get_symbol();
    std::string get_name();
};
