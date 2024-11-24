#include "Food.h"
#include <iostream>

// Default Constructor
Food::Food(GameMechs* thisGMRef)
{
    myGM = thisGMRef;
    foodPos.setObjPos(-10, -10, 'o'); // Initialize the food object outside the gameboard
}


// Destructor
Food::~Food()
{
    // Nothing to clean up for now
}


// Generate food
void Food::generateFood(objPos blockOff)
{
    int randX; int randY;

    // Infinite loop to keep generating until a valid position is found
    while(true) 
    {
        // Generate random x-y coordinates
        randX = rand() % (myGM->getBoardSizeX()-1) + 1; // Generate x in the range [1, xRange-1] -> [1, 18]
        randY = rand() % (myGM->getBoardSizeY()-1) + 1; // Generate y in the range [1, yRange-1] -> [1, 8]

        // Check if the generated position does not conflict with the player's position
        if(randX != blockOff.pos->x || randX != blockOff.pos->y)
        {
            // Valid position found, store it
            foodPos.setObjPos(randX, randY, 'o');
            break; // Exit the loop
        }
    } 
}


// Getter for food position
objPos Food::getFoodPos() const
{
    return foodPos;
}

