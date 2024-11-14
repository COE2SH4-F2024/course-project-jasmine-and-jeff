#include "Player.h"
#include "MacUILib.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    input = STOP;
    
    MacUILib_printf("Player Initialized\n");
    // more actions to be included
    playerPos.pos->x = mainGameMechsRef->getBoardSizeX() / 2;
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY() / 2;
    playerPos.symbol = '@';
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();
    
    if(input != 0)  // Checks to see if input is not null character
    {
        switch(input) // Switch statement to assign direction from input
        {                      
            case ' ':  // exit
                break;
            case 'w':  // up
            case 'W':
                //Direction = UP;
                break;
            case 's':  // down
            case 'S':
                //Direction = DOWN;
                break;
            case 'a':  // left
            case 'A':
                //Direction = LEFT;
                break;
            case 'd':  // right
            case 'D':
                //Direction = RIGHT;
                break;
        }
    }         
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
}

// More methods to be added