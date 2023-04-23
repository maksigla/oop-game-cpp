//
// Created by Max Igla on 08/04/2023.
//

#include "world.h"
#include "animal.h"
#include <ncurses.h>

Animal::Animal() {
    ;
}

Animal::Animal(const int x, const int y, const char &sign, const int &strength, const int &initiative, World* world) 
: Organism(x, y, sign, strength, initiative, world), currWorld(world), sign(sign)
{}

Animal::~Animal() {
    ;
}


void Animal::action() {
    static int canBeCraeted = 0;
    static bool wasCreated = false;
    int currX = this->getX();
    int currY = this->getY();
    Human* humanPtr = dynamic_cast<Human*>(this);
    if(humanPtr != nullptr) return;
    Turtle* turtlePtr = dynamic_cast<Turtle*>(this);
    if (turtlePtr != nullptr) {
        int chanceToStay = currWorld->randomNumber();
        if (chanceToStay < 75) return;
    }
    switch (currWorld->randomMove()) {
        case 1: // go up
            if (currY > 0) {
                Organism* org = currWorld->findOrganism(currX, currY-1);
                if (org == nullptr) {
                    currWorld->moveTo(currX, currY-1, 1, this, currWorld, currX, currY);
                }
                else if ((this->getSign() == org->getSign() && canBeCraeted == 0) || (this->sameSpecies(org) && canBeCraeted == 0)) {
                    this->breed(org);
                    wasCreated = true;
                }
                else {
                    if (this->sameSpecies(org) || this->getSign() == org->getSign()) break;
                    if (this->checkReflection(org, currX, currY)) break;
                    org->collision(org, currX, currY);
                }
            }
            break;

        case 2: // go right
            if (currX < WORLD_X-1) {
                Organism* org = currWorld->findOrganism(currX+1, currY);
                if (org == nullptr) {
                    currWorld->moveTo(currX+1, currY, 1, this, currWorld, currX, currY);
                }
                else if ((this->getSign() == org->getSign() && canBeCraeted == 0) || (this->sameSpecies(org) && canBeCraeted == 0)) {
                    this->breed(org);
                    wasCreated = true;
                }
                else {
                    if (this->sameSpecies(org) || this->getSign() == org->getSign()) break;
                    if (this->checkReflection(org, currX, currY)) break;
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
                else if ((this->getSign() == org->getSign() && canBeCraeted == 0) || (this->sameSpecies(org) && canBeCraeted == 0)) {
                    this->breed(org);
                    wasCreated = true;
                }
                else {
                    if (this->sameSpecies(org) || this->getSign() == org->getSign()) break;
                    if (this->checkReflection(org, currX, currY)) break;
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
                else if ((this->getSign() == org->getSign() && canBeCraeted == 0) || (this->sameSpecies(org) && canBeCraeted == 0)) {
                    this->breed(org);
                    wasCreated = true;
                }
                else {
                    if (this->sameSpecies(org) || this->getSign() == org->getSign()) break;
                    if (this->checkReflection(org, currX, currY)) break;
                    org->collision(this, currX, currY);
                }
            }
            break;
    }
    if (wasCreated) {
        canBeCraeted++;
    }
    if (canBeCraeted == 15) {
        canBeCraeted = 0;
        wasCreated = false;
    }

}

bool Animal::collision(Organism* organism, const int prevX, const int prevY) {
    if (this->getStrength() <= organism->getStrength()) {
        currWorld->removeOrganism(this, organism);
        return true;
    } 
    else {
        currWorld->removeOrganism(organism, this);
    }
    return false;
}

void Animal::draw() {
    ;
}


void Animal::breed(Organism* partner) {
    std::vector<int> coords = currWorld->searchForFreeFields(this, this->getX(), this->getY());
    if (coords[0] != -1 && coords[1] != -1) {
        this->createCopy(coords[0], coords[1]);
        currWorld->addCommunicate("New child of " + std::string(1, this->sign) + " was created!");
    }
}

char Animal::getSign() const {
    return this->sign;
}

void Animal::addStrength() {
    this->strength += 3;
}