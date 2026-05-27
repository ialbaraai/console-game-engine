#include "../include/Entity.h"

#include <iostream>

Entity::Entity(int x, int y, int Damage, int Id)
{
    this->Xposition = x;
    this->Yposition = y;
    this->health = 100;
    this->damage = Damage;
    this->id = Id;
    this->symbol = 'M';
}

int Entity::get_xposition()
{
    return this->Xposition;
}
int Entity::get_yposition()
{
    return this->Yposition;
}
char Entity::get_symbol()
{
    return this->symbol;
}
int Entity::get_health()
{
    return this->health;
}
int Entity::get_damage()
{
    return this->damage;
}
int Entity::get_id()
{
    return this->id;
}

void Entity::move(int x, int y)
{
    this->Xposition += x;
    this->Yposition += y;
}

void Entity::take_damage(int amount)
{
    if(amount > 0)
    {
        if(amount >= this->health)
        {
            this->health -= this->health;
        }
        else
        {
            this->health -= amount;
        }
    }
    else
    {
        std::cout << "Damage is less than 0!\n";
    }
}
