#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "GameMechs.h"


class Food
{
    public:
        Food();
        ~Food();

        void generateFood(objPos blockOff);
        objPos getFoodPos() const;

        private:
        objPos foodPos;

    private:
        // Need a reference to the Main Game Mechanisms
        GameMechs* myGM2;

};

#endif