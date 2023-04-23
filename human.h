#pragma once

#include "animal.h"


// ------ CLASS HUMAN -------

class Human : public Animal 
{

private:
    int x, y;
    World *currWorld;
    bool magicPotionActive = false;
    const int initiative = HUMAN_INITIATIVE;
    int strength = HUMAN_STRENGTH;
    int prevPosX, prevPosY;
    int age = 0;
public:
    Human(const int x, const int y, World* world);
    Human(const int x, const int y, World* world, const int strength);
    ~Human(); 

    bool sameSpecies(Organism* organism) override;
    bool isPotionActive() const;
    int returnStrength() const;
    void action() override;
    bool collision(Organism* organism, const int prevX, const int prevY) override;
    void createCopy(const int x, const int y) override { return; };
    void magicPotion();
    void decreaseMagicPotion();
    void deactivePotion();
    void addStrength() override;
    void setPrevPos(const int x, const int y);

    int loop = 0;
};
