#pragma once

#include "animal.h"

// ------- CLASS ANTELOPE -------

class Antelope : public Animal 
{

private:
    int x, y;
    World *currWorld;
    int age = 0;
    const int initiative = ANTELOPE_INITIATIVE;
    int strength = ANTELOPE_STRENGTH;
    const int sign = ANTELOPE_SIGN;

public: 
    
    Antelope(Organism* organism);
    Antelope(const int x, const int y, World* world);
    Antelope(const int x, const int y, World* world, const int strength);
    ~Antelope();

    void action() override;
    bool collision(Organism* organism, const int prevX, const int prevY) override;
    bool sameSpecies(Organism* organism) override;
    void createCopy(const int x, const int y) override;
    void addStrength() override;
};