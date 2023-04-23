#include "world.h"
#include "antelope.h"
#include <string>

Antelope::Antelope(Organism* organism) {
    organism->setInitiative(ANTELOPE_INITIATIVE);
    organism->setStrength(ANTELOPE_STRENGTH);
    organism->setAge(0);
    std::cout << "Default " << this << " constructor." << std::endl;
}

Antelope::Antelope(const int x, const int y, World* world)
: Animal(x, y, ANTELOPE_SIGN, ANTELOPE_STRENGTH, ANTELOPE_INITIATIVE, world), currWorld(world), x(x), y(y)
{}

Antelope::Antelope(const int x, const int y, World* world, const int strength)
: Animal(x, y, ANTELOPE_SIGN, strength, ANTELOPE_INITIATIVE, world), currWorld(world), x(x), y(y), strength(strength)
{}

Antelope::~Antelope() {
    std::cout << "Default " << this << " destructor." << std::endl;
}

void Antelope::action() {
    static int canBeCreated = 0;
    static bool wasCreated = false;
    srand(time(nullptr));
    int currX = this->getX();
    int currY = this->getY();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 100);

    int random_num = dis(gen);
    
    int randomNum = currWorld->randomNumber();

    if (random_num < 50) {
        switch (currWorld->randomMove()) {
            case 1: // go up
                if (currY > 1) {
                    Organism* org = currWorld->findOrganism(currX, currY-2);
                    if (org == nullptr) {
                        currWorld->moveTo(currX, currY-2, 2, this, currWorld, currX, currY);
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
                if (currX < WORLD_X-2) {
                    Organism* org = currWorld->findOrganism(currX+2, currY);
                    if (org == nullptr) {
                        currWorld->moveTo(currX+2, currY, 2, this, currWorld, currX, currY);
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
                if (currY < WORLD_Y-2) {
                    Organism* org = currWorld->findOrganism(currX, currY+2);
                    if (org == nullptr) {
                        currWorld->moveTo(currX, currY+2, 2, this, currWorld, currX, currY);
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
                if (currX > 1) {
                    Organism* org = currWorld->findOrganism(currX-2, currY);
                    if (org == nullptr) {
                        currWorld->moveTo(currX-2, currY, 2, this, currWorld, currX, currY);
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
    } else {
        switch (currWorld->randomMove()) {
            case 1: // go up
                if (currY > 0) {
                    if (currX > 0) {
                        Organism* org = currWorld->findOrganism(currX-1, currY-1);
                        if (org == nullptr) {
                            currWorld->moveTo(currX-1, currY-1, 1, this, currWorld, currX, currY);
                        }
                        else if ((this->getSign() == org->getSign() && canBeCreated == 0) || (this->sameSpecies(org) && canBeCreated == 0)) {
                            this->breed(org);
                            wasCreated = true;
                        }
                        else {
                            if (this->sameSpecies(org) || this->getSign() == org->getSign()) break;
                            org->collision(this, currX, currY);
                        }
                        
                    } else if (currX < WORLD_X-1) {
                        Organism* org = currWorld->findOrganism(currX+1, currY-1);
                        if (org == nullptr) {
                            currWorld->moveTo(currX+1, currY-1, 1, this, currWorld, currX, currY);
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
                }
                break;

            case 2: // go right
                if (currX < WORLD_X-1) {
                    if (currY > 0) {
                        Organism* org = currWorld->findOrganism(currX+1, currY-1);
                        if (org == nullptr) {
                            currWorld->moveTo(currX+1, currY-1, 1, this, currWorld, currX, currY);
                        }
                        else if ((this->getSign() == org->getSign() && canBeCreated == 0) || (this->sameSpecies(org) && canBeCreated == 0)) {
                            this->breed(org);
                            wasCreated = true;
                        }
                        else {
                            if (this->sameSpecies(org) || this->getSign() == org->getSign()) break;
                            org->collision(this, currX, currY);
                        }
                        
                    } else if (currY < WORLD_Y-1) {
                        Organism* org = currWorld->findOrganism(currX+1, currY+1);
                        if (org == nullptr) {
                            currWorld->moveTo(currX+1, currY+1, 1, this, currWorld, currX, currY);
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
                }   
                break;

            case 3: // go downward
                if (currY < WORLD_Y-1) {
                    if (currX > 0) {
                        Organism* org = currWorld->findOrganism(currX-1, currY+1);
                        if (org == nullptr) {
                            currWorld->moveTo(currX-1, currY+1, 1, this, currWorld, currX, currY);
                        }
                        else if ((this->getSign() == org->getSign() && canBeCreated == 0) || (this->sameSpecies(org) && canBeCreated == 0)) {
                            this->breed(org);
                            wasCreated = true;
                        }
                        else {
                            if (this->sameSpecies(org) || this->getSign() == org->getSign()) break;
                            org->collision(this, currX, currY);
                        }
                        
                    } else if (currX < WORLD_X-1) {
                        Organism* org = currWorld->findOrganism(currX+1, currY+1);
                        if (org == nullptr) {
                            currWorld->moveTo(currX+1, currY+1, 1, this, currWorld, currX, currY);
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
                }
                break;

            case 4: // go left
                if (currX > 0) {
                    if (currY > 0) {
                        Organism* org = currWorld->findOrganism(currX-1, currY-1);
                        if (org == nullptr) {
                            currWorld->moveTo(currX-1, currY-1, 1, this, currWorld, currX, currY);
                        }
                        else if ((this->getSign() == org->getSign() && canBeCreated == 0) || (this->sameSpecies(org) && canBeCreated == 0)) {
                            this->breed(org);
                            wasCreated = true;
                        }
                        else {
                            if (this->sameSpecies(org) || this->getSign() == org->getSign()) break;
                            org->collision(this, currX, currY);
                        }
                        
                    } else if (currY < WORLD_Y-1) {
                        Organism* org = currWorld->findOrganism(currX-1, currY+1);
                        if (org == nullptr) {
                            currWorld->moveTo(currX-1, currY+1, 1, this, currWorld, currX, currY);
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
                }
                break;
        }

    }
    if (wasCreated) {
        canBeCreated++;
    }
    if (canBeCreated == 15) {
        canBeCreated = 0;
        wasCreated = false;
    }
}

bool Antelope::collision(Organism* organism, const int prevX, const int prevY) {
    int num = currWorld->randomNumber();
    if (num < 50) {
        std::vector<int> freeFields = currWorld->searchForFreeFields(this, this->x, this->y);
        currWorld->moveTo(freeFields[0], freeFields[1], 1, this ,currWorld ,this->x, this->y);
        mvprintw(11, WORLD_X+2, "Antelope escaped from attack of %c", this->getSign());
        currWorld->addCommunicate("Antelope escaped the attack from " + std::string(1, organism->getSign()));
        return false;
    }
    if (this->getStrength() <= organism->getStrength()) {
        currWorld->removeOrganism(this, organism);
        return true;
    } 
    else {
        currWorld->removeOrganism(organism, this);
    }
    return false;
}

bool Antelope::sameSpecies(Organism* organism) {
    return dynamic_cast<Antelope*>(organism) != nullptr;
}

void Antelope::createCopy(const int x, const int y) {
    Organism* child = new Antelope(x, y, this->currWorld);
    currWorld->addChild(child);
}

void Antelope::addStrength() {
    this->strength += 3;
}