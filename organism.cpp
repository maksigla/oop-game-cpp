//
// Created by Max Igla on 07/04/2023.
//

#include "world.h"
#include "organism.h"

Organism::Organism() {}

Organism::Organism(int x, int y, const int initiative, const int strength) :
xPos(x), yPos(y), initiative(initiative), strength(strength) {}

Organism::Organism(const int x, const int y, const char &sign, const int &strength, const int &initiative, World* world) 
: xPos(x), yPos(y), sign(sign), strength(strength), initiative(initiative), world(world)
{}

Organism::~Organism() {
    ;
}

void Organism::drawOrganism(char map[][WORLD_X]) {
    map[this->yPos][this->xPos] = this->sign;
}

bool Organism::checkReflection(Organism* organism, const int prevX, const int prevY) {
    Turtle *turtlePtr = dynamic_cast<Turtle*>(organism);
    if (turtlePtr != nullptr && this->getStrength() < 5) {
        this->getWorld()->moveTo(prevX, prevY, 1, this, this->getWorld(), prevX, prevY);
        return true;
    }
    return false;
}

// GETTERS

int Organism::getInitiative() const {
    return this->initiative;
}

int Organism::getStrength() const {
    return this->strength;
}

int Organism::getAge() const {
    return this->age;
}

int Organism::getX() const {
    return this->xPos;
}

int Organism::getY() const {
    return this->yPos;
}

char Organism::getSign() const {
    return this->sign;
}

World* Organism::getWorld() const  {
    return world;
}

// SETTERS

void Organism::setInitiative(const int initiative) {
    this->initiative = initiative;
}

void Organism::setStrength(const int strength) {
    this->strength = strength;
}

void Organism::setAge(const int age) {
    this->age = age;
}

void Organism::setPosition(const int x, const int y) {
    this->xPos = x;
    this->yPos = y;
}

void Organism::setWorld(World* world) {
    this
    ->world = world;
}
void Organism::saveOrganism(Organism* organism, std::ofstream& FILE) {
    std::string strToSave;
    strToSave += organism->getSign();
    strToSave += ';';
    strToSave += std::to_string(organism->getX());
    strToSave += ';';
    strToSave += std::to_string(organism->getY());
    strToSave += ';';
    strToSave += std::to_string(organism->getStrength());
    strToSave += '\n';
    FILE << strToSave;
}
