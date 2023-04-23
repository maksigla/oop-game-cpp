#pragma once

#include "plant.h"

// ------- CLASS SOSNOWSKYS HOGWEED -------

class Sosnowskyshogweed : public Plant 
{
    private:
        World *currWorld;
        int xPos, yPos;
        const int initiative = 0;
        const int strength = SOSNOWSKY_STRENGTH;
        int age = 0;
    public:
        Sosnowskyshogweed();
        Sosnowskyshogweed(const int x, const int y, World* world);
        ~Sosnowskyshogweed();

        void action() override;
        bool collision(Organism* organism, const int prevX, const int prevY) override;
        void createCopy(const int x, const int y) override;
};
