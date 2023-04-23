#pragma once

#include "animal.h"

// ------- CLASS CYBER-SHEEP -------

class Cybersheep : public Animal 
{

private:
    int x, y;
    World *currWorld;
    const int initiative = CYBERSHEEP_INITIATIVE;
    int strength = CYBERSHEEP_STRENGTH;
    const int sign = CYBERSHEEP_SIGN;
    int age = 0;
public:
    Cybersheep(Organism* organism);
    Cybersheep(const int x, const int y, World* world);
    Cybersheep(const int x, const int y, World* world, const int strength);
    ~Cybersheep();

    void action() override;
    bool sameSpecies(Organism* organism) override;
    void createCopy(const int x, const int y) override;
    void addStrength() override;
};
