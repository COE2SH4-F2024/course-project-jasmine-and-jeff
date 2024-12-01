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
void Food::generateFood(objPosArrayList* blockOffList)
{
    int randX; int randY;

    bool validPosition = false;

    // Loop to keep generating food coordinates until a valid position is found
    do 
    {
        // Generate random x-y coordinates
        randX = rand() % (myGM->getBoardSizeX()-2) + 1; // Generate x in the range -> [0,19-2]+1 -> [0,17]+1 -> [1, 18]
        randY = rand() % (myGM->getBoardSizeY()-2) + 1; // Generate y in the range -> [0,9-2]+1  -> [0,7]+1  -> [1, 8]

        validPosition = true;  

        // iterate through every element in player snake
        for(int i = 0; i < blockOffList->getSize(); i++) 
        {
            objPos thisSeg = blockOffList->getElement(i);

            // Check if the generated food position conflicts with any of the player's body positions
            if(randX == thisSeg.pos->x && randY == thisSeg.pos->y) 
            {
                validPosition = false; 
                break; 
            }
        }
    } while(!validPosition);  // Continue generating food if the position is invalid

    // Store the valid food position
    foodPos.setObjPos(randX, randY, 'o');
}


// Getter for food position
objPos Food::getFoodPos() const
{
    return foodPos;
}

