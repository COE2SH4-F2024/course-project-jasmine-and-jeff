#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;

        int boardSizeX;
        int boardSizeY;

        //objPos food;

        // Speed Controls
        int speed;        // Player speed level
        int delayAmount;  // Delay between game loops (microseconds)

    public:
        // Constructors
        GameMechs();
        GameMechs(int boardX, int boardY);

        // Destructor
        ~GameMechs(); // is this one needed at all? Why or why not?
        
        // Getters, Setters and Other
        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const;
        void setLoseFlag();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        
        int getScore() const;
        void incrementScore();
        
        // More methods should be added here
        void collectAsyncInput();

        // Player Speed Controls
        int getSpeed();
        int increaseSpeed();
        int decreaseSpeed();
        int getDelayAmount();
        int setDelayAmount(int this_amount);

        /*
        // Food Generation
        void generateFood(objPos blockOff);
        objPos getFoodPos() const;
        */ 
};

#endif