#include "world.h"
#include "plant.h"
#include <random>

Plant::Plant() {
    ;
}

Plant::Plant(const int x, const int y, const char &sign, const int &strength, const int &initiative, World* world) 
: Organism(x, y, sign, strength, initiative, world), currWorld(world), hasBreed(true), sign(sign)
{}

Plant::~Plant() {
    ;
}

void Plant::action() {
    if(hasBreed) return;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 100);

    int random_num = dis(gen);
    if (random_num < 3) {
        this->breed(this);
        hasBreed = true;
    }
}

bool Plant::collision(Organism* organism, const int prevX, const int prevY) {
    if (this->getStrength() <= organism->getStrength()) {
        currWorld->removeOrganism(this, organism);
        return true;
    } 
    else {
        currWorld->removeOrganism(organism, this);
    }
    return false;
}

void Plant::draw() {
    ;
}

void Plant::breed(Organism* partner) {
    std::vector<int> coords = currWorld->searchForFreeFields(this, this->getX(), this->getY());
    if (coords[0] != -1 && coords[1] != -1) {
        this->createCopy(coords[0], coords[1]);
        currWorld->addCommunicate("New child of " + std::string(1, this->sign) + " was created!");
    }
}

void Plant::changeBreed() {
    hasBreed = false;
}

bool Plant::getBreeded() {
    return hasBreed;
}

char Plant::getSign() const {
    return this->sign;
}