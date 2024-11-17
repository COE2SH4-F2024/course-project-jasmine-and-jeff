#include "Player.h"
#include "MacUILib.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    
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
    char inputChar = mainGameMechsRef->getInput();
    
    switch(inputChar)
    {
        case 'w':
            input = UP;
            break;
        case 's':
            input = DOWN;
            break;
        case 'a':
            input = LEFT;
            break;
        case 'd':
            input = RIGHT;
            break;
        case ' ':
            mainGameMechsRef->setExitTrue();    
            break;
        default:
            // Keep the current direction if input is not recognized
            break;
    }
}
void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    int boardX = mainGameMechsRef->getBoardSizeX();
    int boardY = mainGameMechsRef->getBoardSizeY();

    // Update player position based on direction with wraparound
    switch (input) {
        case UP:
            playerPos.pos->y = (playerPos.pos->y > 1) ? playerPos.pos->y - 1 : boardY - 2;
            break;
        case DOWN:
            playerPos.pos->y = (playerPos.pos->y < boardY - 1 - 1) ? playerPos.pos->y + 1 : 1;
            break;
        case LEFT:
            playerPos.pos->x = (playerPos.pos->x > 1) ? playerPos.pos->x - 1 : boardX - 2;
            break;
        case RIGHT:
            playerPos.pos->x = (playerPos.pos->x < boardX - 1 - 1) ? playerPos.pos->x + 1 : 1;
            break;
        default:
            break;
    }
}
