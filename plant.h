#pragma once

#include "organism.h"

// ------ CLASS PLANTS -------

class Plant : public Organism 
{

private:
    World *currWorld;
    bool hasBreed;
    char sign;
public:
    Plant();
    Plant(const int x, const int y, const char &sign, const int &strength, const int &initiative, World* world);
    virtual ~Plant();
    virtual void action() override;
    virtual bool collision(Organism* organim, const int prevX, const int prevY) override;
    virtual void draw() override;
    void breed(Organism* partner);
    virtual void createCopy(const int x, const int y) = 0;
    void changeBreed();
    bool getBreeded();

    char getSign() const override;
};
