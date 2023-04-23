#pragma once

#include "libs.h"

// ------ CLASS ORGANISM -------

class World;

class Organism 
{
private:
    
protected:
    int strength;
    int initiative;
    int age = 0;
    int xPos, yPos;
    char sign;
    World* world;

public:
    Organism();
    Organism(int x, int y, const int initiative, const int strength);
    Organism(const int x, const int y, const char &sign, const int &strength, const int &initiative, World* world);
    virtual ~Organism();

    virtual void action() = 0; // - basic behavior of organism should be implemented in this method
    virtual bool collision(Organism* organism, const int prevX, const int prevY) = 0; // - behavior of organism in case of collision with other organism
    virtual void draw() = 0; // - method which draws or returns symbolic or graphical representation of the organism

    void drawOrganism(char map[][WORLD_X]);
    bool checkReflection(Organism* organism, const int prevX, const int prevY);

    // getters
    int getInitiative() const;
    int getStrength() const;
    int getAge() const;
    int getX() const;
    int getY() const;
    virtual char getSign() const;
    World* getWorld() const;

    // setters
    void setInitiative(const int initiative);
    void setStrength(const int strength);
    void setAge(const int age);
    void setPosition(const int x, const int y);
    void setWorld(World* world);
    void saveOrganism(Organism* organism, std::ofstream &FILE);

};