#include "../include/Item.h"

#include <string>

Item::Item(std::string Name, int xposition, int yposition, int damage)
{
    this->name = Name;
    this->Xposition = xposition;
    this->Yposition = yposition;
    this->Damage = damage;
    this->symbol = Name[0];
}

int Item::get_xposition()
{
    return this->Xposition;
}
int Item::get_yposition()
{
    return this->Yposition;
}
char Item::get_symbol()
{
    return this->symbol;
}
std::string Item::get_name()
{
    return this->name;
}
