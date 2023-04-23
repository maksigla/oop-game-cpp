#pragma once

#include "organism.h"

// ------ CLASS ANIMALS -------

class Animal : public Organism 
{

private:
    World *currWorld;
    char sign;
public:
    Animal();
    Animal(const int x, const int y, const char &sign, const int &strength, const int &initiative, World* world);
    virtual ~Animal();
    virtual void action() override; // base movement - every typical animal moves to a randomly selected neighboring field
    virtual bool collision(Organism* organism, const int prevX, const int prevY) override; // when two animals of the same species collide,
                      // instead of fighting with each other, both animals remain in their original positions, and
                      // next to them a new animal of their species is created.
    void draw() override;                  
    virtual bool sameSpecies(Organism* organism) = 0;
    void breed(Organism* partner);
    virtual void createCopy(const int x, const int y) = 0;
    virtual void addStrength();

    char getSign() const override;
};
