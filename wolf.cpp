#include "world.h"
#include "wolf.h"


Wolf::Wolf(Organism* organism) {
    organism->setInitiative(WOLF_INITIATIVE);
    organism->setStrength(WOLF_STRENGTH);
    organism->setAge(0);
}

Wolf::Wolf(const int x, const int y, World* world) 
: Animal(x, y, WOLF_SIGN, WOLF_STRENGTH, WOLF_INITIATIVE, world), currWorld(world), x(x), y(y)
{}

Wolf::Wolf(const int x, const int y, World* world, const int strength)
: Animal(x, y, WOLF_SIGN, strength, WOLF_INITIATIVE, world), currWorld(world), x(x), y(y), strength(strength)
{}

Wolf::~Wolf() {

}

bool Wolf::sameSpecies(Organism* organism) {
    return dynamic_cast<Wolf*>(organism) != nullptr;
}

void Wolf::createCopy(const int x, const int y) {
    Organism* child = new Wolf(x, y, this->currWorld);
    currWorld->addChild(child);
}

void Wolf::addStrength() {
    this->strength += 3;
}