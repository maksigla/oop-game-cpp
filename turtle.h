#pragma once

#include "animal.h"

// ------- CLASS TURTLE -------

class Turtle : public Animal 
{

private:
    int x, y;
    World *currWorld;
    const int initiative = TURTLE_INITIATIVE;
    int strength = TURTLE_STRENGTH;
    int age = 0;

public:
    Turtle(Organism* organism); 
    Turtle(const int x, const int y, World* world);
    Turtle(const int x, const int y, World* world, const int strength);
    ~Turtle();

    void action() override;
    bool collision(Organism* organism, const int prevX, const int prevY) override;
    bool sameSpecies(Organism* organism) override;
    void createCopy(const int x, const int y) override;
    void reflectAttack();
    void addStrength() override;
};