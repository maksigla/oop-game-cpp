#include "world.h"
#include "sowthistle.h"
#include <random>

Sowthistle::Sowthistle() {
    std::cout << "Default " << this << " constructor." << std::endl;
}

Sowthistle::Sowthistle(const int x, const int y, World* world)
: Plant(x, y, SOWTHISTLE_SIGN, SOWTHISTLE_STRENGTH, 0, world), currWorld(world), hasBreed(true)
{}

Sowthistle::~Sowthistle() {
        std::cout << "Default " << this << " destructor." << std::endl;
}

void Sowthistle::action() {
    for (int i = 0 ; i < 3 ; i++) {
        if(hasBreed) return;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 100);

        int random_num = dis(gen);
        if (random_num < 3) {
            this->breed(this);
            hasBreed = true;
        }
    }
}

void Sowthistle::createCopy(const int x, const int y) {
    Organism* child = new Sowthistle(x, y, this->currWorld);
    currWorld->addChild(child);
} 

void Sowthistle::changeBreed() {
    hasBreed = false;
}

bool Sowthistle::hasBreeded() {
    return hasBreed;
}