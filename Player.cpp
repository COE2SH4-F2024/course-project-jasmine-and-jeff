#include "Player.h"
#include <iostream>

// Constructor
// ===================================================
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP; // Set the initial direction of the player to STOP

    // more actions to be included

    // Construct player 
    // Starting player position is at middle of board
    playerPos.pos->x = mainGameMechsRef->getBoardSizeX() / 2; 
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY() / 2; 
    playerPos.symbol = '@';
}

// Destructor
// ===================================================
Player::~Player()
{
    // delete any heap members here
    // no keyword "new" in the constructor
    // leave the descructor empty FOR NOW
}

// Other
// ===================================================
objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos array list
    return playerPos; // playerPos holds x, y and symbol 
}

void Player::updatePlayerDir()
{
    // Get input
    char input = mainGameMechsRef -> getInput();

    // PPA2 input processing logic   
    switch(input)
    {                      
        case ' ':  // exit on space key
            // exitFlag = 1; 
            break;

        case 'w':  // Move Up
        case 'W':
            if(myDir != UP && myDir != DOWN) // Move UP only if currently moving horizontally
                myDir = UP;  
            break;

        case 'a':  // Move Left
        case 'A':
            if(myDir != LEFT && myDir != RIGHT) // Move LEFT only if currently moving vertically
                myDir = LEFT;  
            break; 

        case 's':  // Move Down
        case 'S':
            if(myDir != UP && myDir != DOWN) // Move DOWN only if currently moving horizontally
                myDir = DOWN;  
            break; 

        case 'd':  // Move Right
        case 'D':
            if(myDir != LEFT && myDir != RIGHT) // Move RIGHT only if currently moving vertically
                myDir = RIGHT;  

        default:
            break;
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
}

// More methods to be added