#pragma once

#include "plant.h"

// ------- CLASS GUARANA -------

class Guarana : public Plant 
{
    private:
        World *currWorld;
        const int initiative = 0;
        const int strength = GRASS_STRENGTH;
        int age = 0;
    public:
        Guarana();
        Guarana(const int x, const int y, World* world);
        ~Guarana();

        void createCopy(const int x, const int y) override;
        bool collision(Organism* organim, const int prevX, const int prevY) override;
};

