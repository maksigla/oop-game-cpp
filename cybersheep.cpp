#include "world.h"
#include "cybersheep.h"

Cybersheep::Cybersheep(Organism* organism) 
{}

Cybersheep::Cybersheep(const int x, const int y, World* world)
: Animal(x, y, CYBERSHEEP_SIGN, CYBERSHEEP_STRENGTH, CYBERSHEEP_INITIATIVE, world), currWorld(world), x(x), y(y)
{}

Cybersheep::Cybersheep(const int x, const int y, World* world, const int strength)
: Animal(x, y, CYBERSHEEP_SIGN, strength, CYBERSHEEP_INITIATIVE, world), currWorld(world), x(x), y(y), strength(strength)
{}

Cybersheep::~Cybersheep() {
        std::cout << "Default " << this << " destructor." << std::endl;
}

void Cybersheep::action() {
    static int canBeCraeted = 0;
    static bool wasCreated = false;
    int currX = this->getX();
    int currY = this->getY();

    // move to the nearest sosnowskys hogweed
    Organism* nearestHogweed = nullptr; 
    int minDist = WORLD_X + WORLD_Y;  // Initialize minDist to a large value
    for (int i = 0; i < WORLD_X; i++) {
        for (int j = 0; j < WORLD_Y; j++) {
            Organism* org = currWorld->findOrganism(i, j);
            if (org != nullptr && org->getSign() == 'Y') {
                int dist = abs(i - currX) + abs(j - currY);
                if (dist < minDist) {
                    minDist = dist;
                    nearestHogweed = org;
                }
            }
        }
    }

    if (nearestHogweed != nullptr) {
        // Move towards nearest Sosnowsky's hogweed
        int targetX = nearestHogweed->getX();
        int targetY = nearestHogweed->getY();

        if (currX < targetX) {
            // Move right
            currWorld->moveTo(currX+1, currY, 1, this, currWorld, currX, currY);
            if (currX+1 == targetX && currY == targetY) {
                nearestHogweed->collision(this, currX, currY);
            }
        } else if (currX > targetX) {
            // Move left
            currWorld->moveTo(currX-1, currY, 1, this, currWorld, currX, currY);
            if (currX-1 == targetX && currY == targetY) {
                nearestHogweed->collision(this, currX, currY);
            }
        } else if (currY < targetY) {
            // Move down
            currWorld->moveTo(currX, currY+1, 1, this, currWorld, currX, currY);
            if (currX == targetX && currY+1 == targetY) {
                nearestHogweed->collision(this, currX, currY);
            }
        } else if (currY > targetY) {
            // Move up
            currWorld->moveTo(currX, currY-1, 1, this, currWorld, currX, currY);
            if (currX == targetX && currY-1 == targetY) {
                nearestHogweed->collision(this, currX, currY);
            }
        }
    } else {
        switch (currWorld->randomMove()) {
            case 1: // go up
                if (currY > 0) {
                    Organism* org = currWorld->findOrganism(currX, currY-1);
                    if (org == nullptr) {
                        currWorld->moveTo(currX, currY-1, 1, this, currWorld, currX, currY);
                    }
                    else if ((currWorld->returnCybersheepsCount() < 5 && (this->getSign() == org->getSign() && canBeCraeted == 0) || (this->sameSpecies(org) && canBeCraeted == 0))) {
                        this->breed(org);
                        wasCreated = true;
                        currWorld->setCybersheepsCount();
                    }
                    else {
                        if (this->sameSpecies(org)) break;
                        if (this->checkReflection(org, currX, currY)) break;
                        this->collision(org, currX, currY);
                    }
                }
                break;

            case 2: // go right
                if (currX < WORLD_X-1) {
                    Organism* org = currWorld->findOrganism(currX+1, currY);
                    if (org == nullptr) {
                        currWorld->moveTo(currX+1, currY, 1, this, currWorld, currX, currY);
                    }
                    else if ((currWorld->returnCybersheepsCount() < 5 && (this->getSign() == org->getSign() && canBeCraeted == 0) || (this->sameSpecies(org) && canBeCraeted == 0))) {
                        this->breed(org);
                        wasCreated = true;
                        currWorld->setCybersheepsCount();
                    }
                    else {
                        if (this->sameSpecies(org)) break;
                        if (this->checkReflection(org, currX, currY)) break;
                        this->collision(org, currX, currY);
                    }
                }   
                break;

            case 3: // go downward
                if (currY < WORLD_Y-1) {
                    Organism* org = currWorld->findOrganism(currX, currY+1);
                    if (org == nullptr) {
                        currWorld->moveTo(currX, currY+1, 1, this, currWorld, currX, currY);
                    }
                    else if ((currWorld->returnCybersheepsCount() < 5 && (this->getSign() == org->getSign() && canBeCraeted == 0) || (this->sameSpecies(org) && canBeCraeted == 0))) {
                        this->breed(org);
                        wasCreated = true;
                        currWorld->setCybersheepsCount();
                    }
                    else {
                        if (this->sameSpecies(org)) break;
                        if (this->checkReflection(org, currX, currY)) break;
                        this->collision(org, currX, currY);
                    }
                }
                break;

            case 4: // go left
                if (currX > 0) {
                    Organism* org = currWorld->findOrganism(currX-1, currY);
                    if (org == nullptr) {
                        currWorld->moveTo(currX-1, currY, 1, this, currWorld, currX, currY);
                    }
                    else if ((currWorld->returnCybersheepsCount() < 5 && (this->getSign() == org->getSign() && canBeCraeted == 0) || (this->sameSpecies(org) && canBeCraeted == 0))) {
                        this->breed(org);
                        wasCreated = true;
                        currWorld->setCybersheepsCount();
                    }
                    else {
                        if (this->sameSpecies(org)) break;
                        if (this->checkReflection(org, currX, currY)) break;
                        this->collision(org, currX, currY);
                    }
                }
                break;
        }
    }
    if (wasCreated) {
        canBeCraeted++;
    }
    if (canBeCraeted == 15) {
        canBeCraeted = 0;
        wasCreated = false;
    }

}

bool Cybersheep::sameSpecies(Organism* organism) {
    return dynamic_cast<Cybersheep*>(organism) != nullptr;
}

void Cybersheep::createCopy(const int x, const int y) {
    Organism* child = new Cybersheep(x, y, this->currWorld);
    currWorld->addChild(child);
}

void Cybersheep::addStrength() {
    this->strength += 3;
}