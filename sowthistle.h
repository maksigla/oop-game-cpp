#pragma once 

#include "plant.h"

// ------- CLASS SOW_THISTLE -------

class Sowthistle : public Plant 
{
    private:
        World *currWorld;
        bool hasBreed;
        const int initiative = 0;
        const int strength = SOWTHISTLE_STRENGTH;
        const char sign = SOWTHISTLE_SIGN;
        int age = 0;
    public:
        Sowthistle();
        Sowthistle(const int x, const int y, World* world);
        ~Sowthistle();

        void action() override;
        void createCopy(const int x, const int y) override;
        void changeBreed();
        bool hasBreeded();
};
