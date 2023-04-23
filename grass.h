#pragma once

#include "plant.h"

// ------- CLASS GRASS -------

class Grass : public Plant 
{
    private:
        World *currWorld;
        const int initiative = 0;
        const int strength = GRASS_STRENGTH;
        int age = 0;
    public:
        Grass();
        Grass(const int x, const int y, World* world);
        ~Grass(); 

        void createCopy(const int x, const int y) override;
};
