#pragma once

#include <vector>
#include <string>
#include "libs.h"
#include "organism.h"
#include "include_organisms.h"


class World 
{
private:
    // fields for organisms
    unsigned int cybersheepsCount = 0;
    unsigned int roundsLeftToActivatePotion = 0;
    unsigned int round = 0;
    unsigned int x_dim, y_dim;
    bool endTheGame = false;
    char map[WORLD_Y][WORLD_X];
    std::vector<Organism*> organismsAlive;
    std::vector<std::string> communicates;

public:
    // basic constructor
    World();
    // setters and getters
    char getMapPlace(const unsigned int x, const unsigned int y);
    int getNumberOfOrganisms();
    void setMapPlace(const unsigned int x, const unsigned int y, const char c);
    Organism* findOrganism(const int x, const int y);
    Organism* findNotHuman(const int x, const int y);
    std::vector<int> findStrongerOrganisms(const int x, const int y);


    // basic methods for the main class
    void makeTurn();
    void moveEveryOrganism(Organism* organism);
    std::vector<int> searchForFreeFields(Organism* organism, const int x, const int y);
    void drawWorld(const unsigned int x, const unsigned int y);
    void drawHowManyOrganisms();
    int randomNumber();
    int randomNumberFromVector(std::vector<int> v);
    int randomMove();
    void displayOrganisms();
    Organism* checkForCollision(Organism* attacker);
    Organism* checkHumanCollision();
    bool humanAlive();

    // human methods
    void createHuman();
    void changeHumanPosition(const int x, const int y);
    void changePrevHumanPosition(const int x, const int y);
    void activeMagicPotion();
    Human* getHuman() const;

    // add new organism
    void addEverySpecies();
    void addNewOrganism();
    void addNewHuman();
    void addChild(Organism* organism);
    void sortOrganisms(std::vector<Organism*> *organisms);
    bool compareOrganisms(const Organism* a, const Organism* b);

    // remove organism
    void removeOrganism(Organism* victim, Organism *attacker);

    // set random position
    int setRandomX();
    int setRandomY();
    void handleDuplicateCords(int *x, int *y);
    void moveTo(const int x, const int y, const int distance, Organism* organism, World* world, const int prevX, const int prevY);

    void printOrganisms();

    void setCybersheepsCount();
    int returnCybersheepsCount() const;
    void addCommunicate(std::string str);
    void printCommunicates();

    void saveTheGame();
    void loadTheGame();
    void fileData(std::string filename);
    void loadSavedOrganism(std::ifstream &FILE);
    void setGameOver(bool end);
    bool gameOver() const;
};