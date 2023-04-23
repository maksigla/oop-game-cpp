#pragma once

#include "animal.h"


// ------- CLASS SHEEP -------

class Sheep : public Animal 
{

private:
    int x, y;
    World *currWorld;
    const int initiative = SHEEP_INITIATIVE;
    int strength = SHEEP_STRENGTH;
    int age = 0;

public:
    Sheep(Organism* organism);
    Sheep(const int x, const int y, World* world);
    Sheep(const int x, const int y, World* world, const int strength);
    ~Sheep();

    bool sameSpecies(Organism* organism) override;
    void createCopy(const int x, const int y) override;
    void addStrength() override;
};
