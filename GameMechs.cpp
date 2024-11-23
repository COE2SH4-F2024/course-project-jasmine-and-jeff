#include "GameMechs.h"
#include "MacUILib.h"
#include <iostream>

// Constructors
// ===================================================

// Default Constructor
GameMechs::GameMechs()
{
    // Initialize Default values
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    speed = 1;
    delayAmount = 100000;

    boardSizeX = 20; // Default constant width
    boardSizeY = 10; // Default constant height

    food.setObjPos(-10, -10, 'o'); // Initialize the food object outside the gameboard
}

// Parameterized Constructor
GameMechs::GameMechs(int boardX, int boardY)
{
    // Same as Default constructor  
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    // Initialize Board values
    boardSizeX = boardX;
    boardSizeY = boardY;

    food.setObjPos(-10, -10, 'o'); // Initialize the food object outside the gameboard
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    // Nothing on the heap
    // Destructor of gameMechs class can stay empty FOR NOW
}

// Getters
// ===================================================
bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}

void GameMechs::collectAsyncInput()
{
    // Asynchronous Input - non blocking character read-in (Same as PPA1)
    if(MacUILib_hasChar()) // Check if a character is available
    {
        input = MacUILib_getChar(); // Get the character
    }   

    if(input == ' ') // Check exit flag
    {
        setExitTrue(); 
    }   
}

char GameMechs::getInput()
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++; 
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}

// Setters
// ===================================================
void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true; // Set the lose flag to true
}

void GameMechs::setInput(char this_input)
{
    input = this_input; // Assign the provided input
}

void GameMechs::clearInput()
{
    input = 0; // Reset input 
}

// More methods should be added here

// Player Speed Controls
// ===================================================
int GameMechs::getSpeed()
{
    return speed;
}

int GameMechs::increaseSpeed()
{
    if(speed < 5)  // Cap the speed at a maximum level (5x)
    {
        speed++;
        delayAmount = delayAmount / 2;  // Halve the delay amount to increase speed
    }
    return speed;
}

int GameMechs::decreaseSpeed()
{
    if(speed > 1)  // Minimum speed level is 1x
    {
        speed--;
        delayAmount = delayAmount * 2;  // Double the delay amount to decrease speed
    }
    return speed;
}

int GameMechs::getDelayAmount()
{
    return delayAmount;
}

int GameMechs::setDelayAmount(int this_amount)
{
    delayAmount = this_amount;
    return delayAmount;
}


// Food Generation
// ===================================================
void GameMechs::generateFood(objPos blockOff)
{ 
    int randX; int randY;

    // Infinite loop to keep generating until a valid position is found
    while(true) 
    {
        // Generate random x-y coordinates
        randX = rand() % (getBoardSizeX()-1) + 1; // Generate x in the range [1, xRange-1] -> [1, 18]
        randY = rand() % (getBoardSizeY()-1) + 1; // Generate y in the range [1, yRange-1] -> [1, 8]

        // Check if the generated position does not conflict with the player's position
        if(randX != blockOff.pos->x || randX != blockOff.pos->y)
        {
            // Valid position found, store it
            food.setObjPos(randX, randY, 'o');
            break; // Exit the loop
        }
    } 
}

objPos GameMechs::getFoodPos() const
{
    return food;
}