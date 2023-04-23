#pragma once

#include "plant.h"

// ------- CLASS BELLADONNA -------

class Belladonna : public Plant 
{
    private:
        World *currWorld;
        const int initiative = 0;
        const int strength = BELLADONNA_STRENGTH;
        int age = 0;
    public:
        Belladonna();
        Belladonna(const int x, const int y, World* world);
        ~Belladonna();

        void createCopy(const int x, const int y) override;
};
