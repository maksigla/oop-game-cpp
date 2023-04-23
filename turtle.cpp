#include "world.h"
#include "turtle.h"

Turtle::Turtle(Organism* organism) {
    organism->setInitiative(TURTLE_INITIATIVE);
    organism->setStrength(TURTLE_STRENGTH);
    organism->setAge(0);
    std::cout << "Default " << this << " constructor." << std::endl;
}

Turtle::Turtle(const int x, const int y, World* world)
: Animal(x, y, TURTLE_SIGN, TURTLE_STRENGTH, TURTLE_INITIATIVE, world), currWorld(world), x(x), y(y)
{}

Turtle::Turtle(const int x, const int y, World* world, const int strength) 
: Animal(x, y, TURTLE_SIGN, strength, TURTLE_INITIATIVE, world), currWorld(world), x(x), y(y), strength(strength)
{}

Turtle::~Turtle() 
{}

bool Turtle::collision(Organism* organism, const int prevX, const int prevY) {
    if (organism->getStrength() < 5) {
        mvprintw(8, WORLD_X+3, "Turtle reflected the attack!");
        currWorld->addCommunicate("Turtle reflected the attack of " + std::string(1, organism->getSign()));
        organism->setPosition(prevX, prevY);
        currWorld->setMapPlace(prevX, prevY, organism->getSign());
        return false;
    } else {
        currWorld->removeOrganism(this, organism);
        return true;
    }
    return false;
}

void Turtle::action() {
    static int canBeCreated = 0;
    static bool wasCreated = false;
    int currX = this->getX();
    int currY = this->getY();
    int chanceToStay = currWorld->randomNumber();
    if (chanceToStay < 75) {
        mvprintw(9, WORLD_X+2, "Turtle stayed in the same place");
        currWorld->addCommunicate("Turtle stayed in the same place");
        return;
    }
    switch (currWorld->randomMove()) {
        case 1: // go up
            if (currY > 0) {
                Organism* org = currWorld->findOrganism(currX, currY-1);
                if (org == nullptr) {
                    currWorld->moveTo(currX, currY-1, 1, this, currWorld, currX, currY);
                }
                else if ((this->getSign() == org->getSign() && canBeCreated == 0) || (this->sameSpecies(org) && canBeCreated == 0)) {
                    this->breed(org);
                    wasCreated = true;
                }
                else {
                    if (this->sameSpecies(org) || this->getSign() == org->getSign()) break;
                    org->collision(this, currX, currY);
                }
            }
            break;

        case 2: // go right
            if (currX < WORLD_X-1) {
                Organism* org = currWorld->findOrganism(currX+1, currY);
                if (org == nullptr) {
                    currWorld->moveTo(currX+1, currY, 1, this, currWorld, currX, currY);
                }
                else if ((this->getSign() == org->getSign() && canBeCreated == 0) || (this->sameSpecies(org) && canBeCreated == 0)) {
                    this->breed(org);
                    wasCreated = true;
                }
                else {
                    if (this->sameSpecies(org) || this->getSign() == org->getSign()) break;
                    org->collision(this, currX, currY);
                }
            }   
            break;

        case 3: // go downward
            if (currY < WORLD_Y-1) {
                Organism* org = currWorld->findOrganism(currX, currY+1);
                if (org == nullptr) {
                    currWorld->moveTo(currX, currY+1, 1, this, currWorld, currX, currY);
                }
                else if ((this->getSign() == org->getSign() && canBeCreated == 0) || (this->sameSpecies(org) && canBeCreated == 0)) {
                    this->breed(org);
                    wasCreated = true;
                }
                else {
                    if (this->sameSpecies(org) || this->getSign() == org->getSign()) break;
                    org->collision(this, currX, currY);
                }
            }
            break;

        case 4: // go left
            if (currX > 0) {
                Organism* org = currWorld->findOrganism(currX-1, currY);
                if (org == nullptr) {
                    currWorld->moveTo(currX-1, currY, 1, this, currWorld, currX, currY);
                }
                else if ((this->getSign() == org->getSign() && canBeCreated == 0) || (this->sameSpecies(org) && canBeCreated == 0)) {
                    this->breed(org);
                    wasCreated = true;
                }
                else {
                    if (this->sameSpecies(org) || this->getSign() == org->getSign()) break;
                    org->collision(this, currX, currY);
                }
            }
            break;
    }
    if (wasCreated) {
        canBeCreated++;
    }
    if (canBeCreated == 15) {
        canBeCreated = 0;
        wasCreated = false;
    }
}

bool Turtle::sameSpecies(Organism* organism) {
    return dynamic_cast<Turtle*>(organism) != nullptr;
}

void Turtle::createCopy(const int x, const int y) {
    Organism* child = new Turtle(x, y, this->currWorld);
    currWorld->addChild(child);
}

void Turtle::addStrength() {
    this->strength += 3;
}