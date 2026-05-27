#include "../include/Game.h"

#include <iostream>
#include <fstream>


Game::Game(const std::string& filepath, Player *player, std::vector<Entity> *entities, std::vector<Item> *items, bool combat, bool collide, bool end)
{
    this->currentPlayer = *player;
    
    for(Entity entity : *entities)
    {
        this->currentEntities.push_back(entity);
        this->currentEntitiesAmount++;
    }

    for(Item item : *items)
    {
        this->currentItems.push_back(item);
        this->currentItemsAmount++;
    }

    this->map_lines = 0;
    this->IS_RUNNING = true;
    this->is_combat = false;

    this->IS_COLLIDE = collide;
    this->IS_COMBAT = combat;
    this->IS_END = end;

    load_map(filepath);
}

void Game::clear_screen()
{
    std::cout << "\033[2J\033[H";
}

void Game::run()
{
    while(this->IS_RUNNING)
    {
        this->render();

        if(this->IS_COLLIDE)
        {
            this->check_collision();
        }

        this->update();
        this->move_entities();
    }
}
void Game::load_map(std::string filename)
{
    std::ifstream file_content;
    file_content.open(filename);

    if(file_content.is_open())
    {
        std::string curLine;
        while(std::getline(file_content, curLine))
        {
            this->map.push_back(curLine);
            this->map_lines++;
        }

        file_content.close();
    }
}

void Game::render()
{
    this->clear_screen();

    for(int y = 0; y < this->map_lines; y++)
    {
        std::string temp_line = this->map[y];

        for(int x = 0; x < this->map[y].length(); x++)
        {
            for(Entity entity : this->currentEntities)
            {
                if(entity.get_xposition() == x && entity.get_yposition() == y)
                {
                    temp_line[x] = entity.get_symbol();
                }
            }

            for(Item item : this->currentItems)
            {
                if(item.get_xposition() == x && item.get_yposition() == y)
                {
                    temp_line[x] = item.get_symbol();
                }
            }

            if(currentPlayer.get_xposition() == x && currentPlayer.get_yposition() == y)
            {
                temp_line[x] = currentPlayer.get_symbol();
            }
        }

        std::cout << temp_line << std::endl;
    }

    std::map<std::string, int> inventory = this->currentPlayer.get_items();

    std::cout << "Inventory: ";

    for(const auto &pair : inventory)
    {
        std::cout << pair.first << " x" << pair.second << ". ";
    }

    std::cout << std::endl;

    std::cout << "Player Health: " << this->currentPlayer.get_health() << "%\n";
    
    std::cout << "-----------------------------------" << std::endl;
}

char Game::process_input()
{
    char input;
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Click any key (Q to quit): ";
    std::cin >> input;

    return input;
}

void Game::update()
{
    if(this->IS_RUNNING == true)
    {
        char input = this->process_input();
        bool result = false;

        if(input == 'w' || input == 'W')
        {   
            result = this->move_player(0, -1);
        }
        else if(input == 'a' || input == 'A')
        {
            result = this->move_player(-1, 0);
        }
        else if(input == 's' || input == 'S')
        {
            result = this->move_player(0, 1);
        }
        else if(input == 'd' || input == 'D')
        {
            result = this->move_player(1, 0);
        }
        else if(input == 'q' || input == 'Q')
        {
            result = true;
            char confirmation;
            std::cin.ignore();
            std::cout << "Are you sure (y/n)?: ";
            std::cin >> confirmation;

            if(confirmation == 'y' || confirmation == 'Y')
            {
                this->IS_RUNNING = false;
            }
        }
        else
        {
            std::cout << "Invalid input!\n";
        }

        if(result == false)
        {
            std::cout << "Invalid move!\n";
            this->update();
        }
    }
}

bool Game::move_player(int x, int y)
{
    try
    {
        int newPlayerXPos = this->currentPlayer.get_xposition() + x;
        int newPlayerYPos = this->currentPlayer.get_yposition() + y;

        if(newPlayerYPos >= 0 && newPlayerYPos < map.size())
        {
            if(newPlayerXPos >= 0 && newPlayerXPos < map[newPlayerYPos].length())
            {
                if(this->map[newPlayerYPos][newPlayerXPos] != '#')
                {
                    this->currentPlayer.move(x, y);

                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    
}

void Game::move_entities()
{
    for(Entity &curEntity : this->currentEntities)
    {
        if(this->currentPlayer.get_xposition() > curEntity.get_xposition())
        {
            int newXPos = curEntity.get_xposition() + 1;

            if(newXPos >= 0 && newXPos < map[curEntity.get_yposition()].length())
            {
                if(map[curEntity.get_yposition()][newXPos] != '#')
                {
                    curEntity.move(1, 0);
                }
            }

        }
        else if(this->currentPlayer.get_xposition() < curEntity.get_xposition())
        {
            int newXPos = curEntity.get_xposition() - 1;

            if(newXPos >= 0 && newXPos < map[curEntity.get_yposition()].length())
            {
                if(map[curEntity.get_yposition()][newXPos] != '#')
                {
                    curEntity.move(-1, 0);
                }
            }
        }
        else
        {
            if(this->currentPlayer.get_yposition() > curEntity.get_yposition())
            {
                int newYPos = curEntity.get_yposition() + 1;

                if(newYPos >= 0 && newYPos < map.size())
                {
                    if(map[newYPos][curEntity.get_xposition()] != '#')
                    {
                        curEntity.move(0, 1);
                    }
                }
            }
            else if(this->currentPlayer.get_yposition() < curEntity.get_xposition())
            {
                int newYPos = curEntity.get_yposition() - 1;

                if(newYPos >= 0 && newYPos < map.size())
                {
                    if(map[newYPos][curEntity.get_xposition()] != '#')
                    {
                        curEntity.move(0, -1);
                    }
                }
            }
        }
    }
}

void Game::check_collision()
{
    for(Entity &entity : this->currentEntities)
    {
        if(this->currentPlayer.get_xposition() == entity.get_xposition() && this->currentPlayer.get_yposition() == entity.get_yposition())
        {
            if(this->IS_COMBAT)
            {
                currentPlayer.combat(entity);
                this->handle_combat(&entity);
            }
        }
    }

    for(Item &item : this->currentItems)
    {
        if(this->currentPlayer.get_xposition() == item.get_xposition() && this->currentPlayer.get_yposition() == item.get_yposition())
        {
            currentPlayer.pickup(item);
            std::cout << "You found a " << item.get_name() << '\n';

            for(int i = 0; i < this->currentItemsAmount; i++)
            {
                if(item.get_xposition() == this->currentItems[i].get_xposition() && item.get_yposition() == this->currentItems[i].get_yposition())
                {
                    this->currentItems.erase(this->currentItems.begin() + i);
                    currentItemsAmount--;
                    break;
                }
            }
        }
    }
}

void Game::handle_combat(Entity *entity)
{
    std::cout << "A monster!\n";

    char option = '\0';

    bool PlayerAlive = true;
    bool EntityAlive = true;
    bool runResult = false;

    do
    {
        std::cout << "Press Enter to continue...";
        std::cin;

        std::cout << "Player Health: " << this->currentPlayer.get_health() << "/100\n";
        std::cout << "Enemy Health: " << entity->get_health() << "/100\n";

        std::cout << "What do you want to do? [F]ight or [R]un: ";
        std::cin >> option;

        if(option == 'f' || option == 'F')
        {
            std::cout << "Player chose to fight!\n\n";

            entity->take_damage(this->currentPlayer.get_damage());

            std::cout << "Player deals " << this->currentPlayer.get_damage() << " damage to Enemy!\n";

            if(entity->get_health() <= 0)
            {
                EntityAlive = false;
                break;
            }

            this->currentPlayer.take_damage(entity->get_damage());

            std::cout << "Enemy deals " << entity->get_damage() << " damage to Player!\n";

            if(this->currentPlayer.get_health() <= 0)
            {
                PlayerAlive = false;
                break;
            }
        }
        else if(option == 'r' || option == 'R')
        {
            runResult = this->move_player(2, 0);

            if(runResult == false)
            {
                runResult = this->move_player(-2, 0);

                if(runResult == false)
                {
                    runResult = this->move_player(0, 2);

                    if(runResult == false)
                    {
                        runResult = this->move_player(0, -2);
                    }
                }
            }

            break;
        }
        else
        {
            std::cout << "Invalid Input!\n";
        }

    } while (PlayerAlive && EntityAlive);

    if(!PlayerAlive)
    {
        if(this->IS_END)
        {
            this->is_game_over();
        }
    }
    else if(!EntityAlive)
    {
        std::cout << "You survived!\n";

        for(int i = 0; i < this->currentEntities.size(); i++)
        {
            if(currentEntities[i].get_id() == entity->get_id())
            {
                this->currentEntities.erase(this->currentEntities.begin() + i);
                currentEntitiesAmount--;
                break;
            }
        }
    }
}

void Game::is_game_over()
{
    if(this->currentPlayer.get_health() <= 0)
    {
        this->IS_RUNNING = false;
        std::cout << "Game over, you lost!\n";
    }
}
