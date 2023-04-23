#include "world.h"
#include "sheep.h"

Sheep::Sheep(Organism* organism) {
    organism->setInitiative(SHEEP_INITIATIVE);
    organism->setStrength(SHEEP_STRENGTH);
    organism->setAge(0);
    std::cout << "Default " << this << " constructor." << std::endl;
}

Sheep::Sheep(const int x, const int y, World* world)
: Animal(x, y, SHEEP_SIGN, SHEEP_STRENGTH, SHEEP_INITIATIVE, world), currWorld(world), x(x), y(y)
{}

Sheep::Sheep(const int x, const int y, World* world, const int strength)
: Animal(x, y, SHEEP_SIGN, strength, SHEEP_INITIATIVE, world), currWorld(world), x(x), y(y), strength(strength)
{}

Sheep::~Sheep() {
    std::cout << "Default " << this << " destructor." << std::endl;
}

bool Sheep::sameSpecies(Organism* organism) {
    return dynamic_cast<Sheep*>(organism) != nullptr;
}

void Sheep::createCopy(const int x, const int y) {
    Organism* child = new Sheep(x, y, this->currWorld);
    currWorld->addChild(child);
}

void Sheep::addStrength() {
    this->strength += 3;
}
