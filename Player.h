#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        // Constructor
        Player(GameMechs* thisGMRef);

        // Destructor
        ~Player();

        // Other
        objPos getPlayerPos() const; // Upgrade this in iteration 3.       
        void updatePlayerDir();
        void movePlayer();

        // More methods to be added here

    private:
        objPos playerPos;  // This is the Player's position (object of the OBJPOS class) which is holding player's x,y position and symbol
                        // Upgrade this in iteration 3.     

        enum Dir myDir;  // Declare a variable "myDir" to hold the current direction

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif