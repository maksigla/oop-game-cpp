#pragma once 

#include "animal.h"

// ------- CLASS WOLF -------

class Wolf : public Animal 
{

private:
    int x, y;
    World *currWorld;
    const int initiative = WOLF_INITIATIVE;
    int strength = WOLF_STRENGTH;
    int age = 0;

public:
    Wolf(Organism* organism);
    Wolf(const int x, const int y, World* world);
    Wolf(const int x, const int y, World* world, const int strength);
    ~Wolf();

    bool sameSpecies(Organism* organism) override;
    void createCopy(const int x, const int y) override;
    void addStrength() override;
};
