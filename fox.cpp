#include "world.h"
#include "fox.h"

Fox::Fox(Organism* organism) {
    organism->setInitiative(FOX_INITIATIVE);
    organism->setStrength(FOX_STRENGTH);
    organism->setAge(0);
    std::cout << "Default " << this << " constructor." << std::endl;
}

Fox::Fox(const int x, const int y, World* world)
: Animal(x, y, FOX_SIGN, FOX_STRENGTH, FOX_INITIATIVE, world), currWorld(world), x(x), y(y)
{}

Fox::Fox(const int x, const int y, World* world, const int strength)
: Animal(x, y, FOX_SIGN, strength, FOX_INITIATIVE, world), currWorld(world), x(x), y(y), strength(strength)
{}

Fox::~Fox() {
    std::cout << "Default " << this << " destructor." << std::endl;
}

void Fox::action() {
    int currX = this->getX();
    int currY = this->getY();
    std::vector<int> blockedFields = currWorld->findStrongerOrganisms(currX, currY);
    switch (currWorld->randomMove()) {
        case 1: // go up
            if (currY > 0 && std::find(blockedFields.begin(), blockedFields.end(), 1) == blockedFields.end()) {
                currWorld->moveTo(currX, currY-1, 1, this, currWorld, currX, currY);
                currWorld->setMapPlace(currX, currY, '+'); // reset map 
            }
            break;

        case 2: // go right
            if (currX < WORLD_X-1 && std::find(blockedFields.begin(), blockedFields.end(), 2) == blockedFields.end()) {
                currWorld->moveTo(currX+1, currY, 1, this, currWorld, currX, currY);
                currWorld->setMapPlace(currX, currY, '+'); // reset map 
            }   
            break;

        case 3: // go downward
            if (currY < WORLD_Y-1 && std::find(blockedFields.begin(), blockedFields.end(), 3) == blockedFields.end()) {
                currWorld->moveTo(currX, currY+1, 1, this, currWorld, currX, currY);
                currWorld->setMapPlace(currX, currY, '+'); // reset map 
            }
            break;

        case 4: // go left
            if (currX > 0 && std::find(blockedFields.begin(), blockedFields.end(), 4) == blockedFields.end()) {
                currWorld->moveTo(currX-1, currY, 1, this, currWorld, currX, currY);
                currWorld->setMapPlace(currX, currY, '+'); // reset map 
            }
            break;
    }
}

bool Fox::sameSpecies(Organism* organism) {
    return dynamic_cast<Fox*>(organism) != nullptr;
}

void Fox::createCopy(const int x, const int y) {
    Organism* child = new Fox(x, y, this->currWorld);
    currWorld->addChild(child);
}

void Fox::addStrength() {
    this->strength += 3;
}
