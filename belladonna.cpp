#include "world.h"
#include "belladonna.h"

Belladonna::Belladonna() {
    std::cout << "Default " << this << " constructor." << std::endl;
}

Belladonna::Belladonna(const int x, const int y, World* world) 
: Plant(x, y, BELLADONNA_SIGN, BELLADONNA_STRENGTH, 0, world), currWorld(world)
{}

Belladonna::~Belladonna() {
    std::cout << "Default " << this << " destructor." << std::endl;
}

void Belladonna::createCopy(const int x, const int y) {
    Organism* child = new Belladonna(x, y, this->currWorld);
    currWorld->addChild(child);
}