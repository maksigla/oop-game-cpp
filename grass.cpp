#include "world.h"
#include "grass.h"

Grass::Grass() {
    std::cout << "Default " << this << " constructor." << std::endl;
}

Grass::Grass(const int x, const int y, World* world)
: Plant(x, y, GRASS_SIGN, GRASS_STRENGTH, 0, world), currWorld(world)
{}


Grass::~Grass() {
        std::cout << "Default " << this << " destructor." << std::endl;
}


void Grass::createCopy(const int x, const int y) {
    Organism* child = new Grass(x, y, this->currWorld);
    currWorld->addChild(child);
}