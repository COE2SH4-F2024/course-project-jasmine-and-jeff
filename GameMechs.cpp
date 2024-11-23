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
    

char GameMechs::getInput()
{
    // Asynchronous Input - non blocking character read-in (Same as PPA1)
    if(MacUILib_hasChar()) // Check if a character is available
    {
        input = MacUILib_getChar(); // Get the character
    }   

    if(input == ' ') // exit on space key
    {
        setExitTrue(); 
    }   
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