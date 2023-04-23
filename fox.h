#pragma once

#include "animal.h"

// ------- CLASS FOX -------

class Fox : public Animal 
{

private:
    int x, y;
    World *currWorld;
    const int initiative = FOX_INITIATIVE;
    int strength = FOX_STRENGTH;
    int age = 0;
    
public:
    Fox(Organism* organism);
    Fox(const int x, const int y, World* world);
    Fox(const int x, const int y, World* world, const int strength);
    ~Fox();

    void action() override;
    bool sameSpecies(Organism* organism) override;
    void createCopy(const int x, const int y) override;
    void addStrength() override;
};