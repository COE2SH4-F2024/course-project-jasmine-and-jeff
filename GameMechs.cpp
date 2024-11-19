#include "GameMechs.h"
#include "MacUILib.h"

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

    boardSizeX = 20;
    boardSizeY = 10;
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

}
    

char GameMechs::getInput()
{
    // Asynchronous Input - non blocking character read-in (Same as PPA1)
    if(MacUILib_hasChar()) // Check if a character is available
    {
        input = MacUILib_getChar(); // Get the character
    }   
}

int GameMechs::getScore() const
{

}

void GameMechs::incrementScore()
{
    
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

}

void GameMechs::setLoseFlag()
{
    
}

void GameMechs::setInput(char this_input)
{

}

void GameMechs::clearInput()
{

}

// More methods should be added here