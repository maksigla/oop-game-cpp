#include "human.h"
#include "world.h"

/*
Human::Human() {
    ;
}
*/

Human::Human(const int x, const int y, World* world)
: Animal(x, y, HUMAN_SIGN, HUMAN_STRENGTH, HUMAN_INITIATIVE, world), currWorld(world), x(x), y(y)
{}

Human::Human(const int x, const int y, World* world, const int strength)
: Animal(x, y, HUMAN_SIGN, strength, HUMAN_INITIATIVE, world), currWorld(world), x(x), y(y), strength(strength)
{}

Human::~Human() {
    ;
}

void Human::action() {
        currWorld->printCommunicates();
        loop = getch();
        switch (loop) {
            case KEY_UP:
                if (this->y > 0) {
                    Organism* org = currWorld->findNotHuman(this->x, this->y-1);
                    if (org == nullptr) {
                        this->y--;
                        currWorld->changeHumanPosition(this->x, this->y);
                    } else {
                        if(org->collision(this, this->x, this->y-1)) {
                            this->y--;
                            currWorld->changeHumanPosition(this->x, this->y);
                        }
                    }
                }
                break;
            case KEY_DOWN:
                if (this->y < WORLD_Y-1) {
                    Organism* org = currWorld->findNotHuman(this->x, this->y+1);
                    if (org == nullptr) {
                        this->y++;
                        currWorld->changeHumanPosition(this->x, this->y);
                    } else {
                        if(org->collision(this, this->x, this->y+1)) {
                            this->y++;
                            currWorld->changeHumanPosition(this->x, this->y);
                        }
                    }
                }
                break;
            case KEY_LEFT:
                if (this->x > 0) {
                    Organism* org = currWorld->findNotHuman(this->x-1, this->y);
                    if (org == nullptr) {
                        this->x--;
                        currWorld->changeHumanPosition(this->x, this->y);
                    } else {
                        if (org->collision(this, this->x-1, this->y)) {
                            this->x--;
                            currWorld->changeHumanPosition(this->x, this->y);
                        }
                    }
                }
                break;
            case KEY_RIGHT:
                if (this->x < WORLD_X-1) {
                    Organism* org = currWorld->findNotHuman(this->x+1, this->y);
                    if (org == nullptr) {
                        this->x++;
                        currWorld->changeHumanPosition(this->x, this->y);
                    } else {
                        if (org->collision(this, this->x+1, this->y)) {
                            this->x++;
                            currWorld->changeHumanPosition(this->x, this->y);
                        }
                    }
                }
                break;
            case 'm':
                currWorld->activeMagicPotion();
                break;
            case 's':
                currWorld->saveTheGame();
                break;
            case 'l':
                currWorld->loadTheGame();
                break;
            case 'q':
                currWorld->setGameOver(true);
                loop = 'q';
                break;
        }
}

bool Human::collision(Organism* organism, const int prevX, const int prevY) {
    if (this->getStrength() <= organism->getStrength()) {
        currWorld->removeOrganism(this, organism);
        return true;
    } 
    else {
        currWorld->removeOrganism(organism, this);
    }
    return false;
}


bool Human::sameSpecies(Organism* organism) {
    return false;
}

bool Human::isPotionActive() const {
    return magicPotionActive;
}

int Human::returnStrength() const {
    return strength;
}

void Human::magicPotion() {
    this->magicPotionActive = true;
    this->strength = 10;
}

void Human::decreaseMagicPotion() {
    this->strength--;
}

void Human::deactivePotion() {
    this->magicPotionActive = false;
}

void Human::addStrength() {
    this->strength += 3;
}

void Human::setPrevPos(const int x, const int y) {
    this->prevPosX = x;
    this->prevPosY = y;
}