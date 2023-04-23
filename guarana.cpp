#include "world.h"
#include "guarana.h"

Guarana::Guarana() {
    std::cout << "Default " << this << " constructor." << std::endl;
}

Guarana::Guarana(const int x, const int y, World* world) 
: Plant(x, y, GUARANA_SIGN, GUARANA_STRENGTH, 0, world), currWorld(world)
{}

Guarana::~Guarana() {
        std::cout << "Default " << this << " destructor." << std::endl;
}

void Guarana::createCopy(const int x, const int y) {
    Organism* child = new Guarana(x, y, this->currWorld);
    currWorld->addChild(child);
}


bool Guarana::collision(Organism* organism, const int prevX, const int prevY) {
    Animal* animalPtr = dynamic_cast<Animal*>(organism);
    if (animalPtr != nullptr) animalPtr->addStrength();
    if (this->getStrength() <= organism->getStrength()) {
        currWorld->removeOrganism(this, organism);
        return true;
    } 
    else {
        currWorld->removeOrganism(organism, this);
    }
    return false;
}