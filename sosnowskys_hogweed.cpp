#include "world.h"
#include "sosnowsky.h"

Sosnowskyshogweed::Sosnowskyshogweed() {
    std::cout << "Default " << this << " constructor." << std::endl;
}

Sosnowskyshogweed::Sosnowskyshogweed(const int x, const int y, World* world) 
: Plant(x, y, SOSNOWSKY_SIGN, SOSNOWSKY_STRENGTH, 0, world), currWorld(world), xPos(x), yPos(y)
{}

Sosnowskyshogweed::~Sosnowskyshogweed() {
        std::cout << "Default " << this << " destructor." << std::endl;
}

void Sosnowskyshogweed::action() {
    int x = this->xPos;
    int y = this->yPos;
    for (int i = x-1; i <= x+1; i++) {
        for (int j = y-1; j <= y+1; j++) {
            if (i == x && j == y) continue;  // Skip the plant itself
            Organism* org = currWorld->findOrganism(i, j);
            Cybersheep* cybersheep = dynamic_cast<Cybersheep*>(org);
            if (org != nullptr && cybersheep == nullptr) {
                currWorld->removeOrganism(org, this);
                delete org;
            }
        }
    }
}

bool Sosnowskyshogweed::collision(Organism* organism, const int prevX, const int prevY) {
    if(dynamic_cast<Cybersheep*>(organism) != nullptr) {
        currWorld->removeOrganism(this, organism);
        return true;
    }
    return false;
}

void Sosnowskyshogweed::createCopy(const int x, const int y) {
    Organism* child = new Antelope(x, y, this->currWorld);
    currWorld->addChild(child);
}