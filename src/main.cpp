#include "../include/Game.h"

int main()
{
    Player currentPlayer;
    Entity firstEntity(4, 4, 10, 1);
    Entity secondEntity(5, 5, 10, 2);
    Entity thirdEntity(6, 6, 10, 3);
    Item firstItem("Key", 3, 3, 0);
    Item secondItem("Bread", 9, 4, 0);
    Item thirdItem("Sword", 10, 1, 100);
    Item fourthItem("Bread", 5, 2, 0);
    Item fifthItem("Bandage", 6, 7, 0);

    std::vector<Entity> currentEntities = {firstEntity, secondEntity, thirdEntity};
    std::vector<Item> currentItems = {firstItem, secondItem, thirdItem, fourthItem}; 

    Game myGame("assets/map1.txt", &currentPlayer, &currentEntities, &currentItems, true, true, true);
    myGame.run();

    return 0;
}
