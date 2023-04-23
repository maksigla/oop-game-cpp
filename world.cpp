//
// Created by Max Igla on 07/04/2023.
//


#include "world.h"


World::World() {
    this->addNewHuman();
    for (int i = 0; i < WORLD_Y; i++) {
        for (int j = 0; j < WORLD_X; j++) {
            map[i][j] = '+';
        }
    }
}

char World::getMapPlace(const unsigned int x, const unsigned int y) {
    return map[y][x];
}

int World::getNumberOfOrganisms() {
    return organismsAlive.size();
}

void World::setMapPlace(const unsigned int x, const unsigned int y, const char c) {
    map[y][x] = c;
}

Organism* World::findOrganism(const int x, const int y) {
    for (auto organism : organismsAlive) {
        if (organism->getX() == x && organism->getY() == y) {
            return organism;
        }
    }
    return nullptr;
}

Organism* World::findNotHuman(const int x, const int y) {
    for (auto organism : organismsAlive) {
        if (dynamic_cast<Human*>(organism) == nullptr && organism->getX() == x && organism->getY() == y) {
            return organism;
        }
    }
    return nullptr;
}

std::vector<int> World::findStrongerOrganisms(const int x, const int y) {
    std::vector<int> directions;

    // check north
    if (y > 0 && this->getMapPlace(x, y-1) != '+') {
        Organism* opponent = this->findOrganism(x, y-1);
        if (opponent != nullptr && opponent->getStrength() > FOX_STRENGTH) {
            directions.push_back(1);
        }
    }
    
    // Check east
    if (x < WORLD_X-1 && this->getMapPlace(x+1, y) != '+') {
        Organism* opponent = this->findOrganism(x+1, y);
        if (opponent != nullptr && opponent->getStrength() > FOX_STRENGTH) {
            directions.push_back(2);
        }
    }
    
    // Check south
    if (y < WORLD_Y-1 && this->getMapPlace(x, y+1) != '+') {
        Organism* opponent = this->findOrganism(x, y+1);
        if (opponent != nullptr && opponent->getStrength() > FOX_STRENGTH) {
            directions.push_back(3);
        }
    }
    
    // Check west
    if (x > 0 && this->getMapPlace(x-1, y) != '+') {
        Organism* opponent = this->findOrganism(x-1, y);
        if (opponent != nullptr && opponent->getStrength() > FOX_STRENGTH) {
            directions.push_back(4);
        }
    }

    return directions;
}

void World::makeTurn() {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);

    if (round == 0) {
        this->addEverySpecies();
        //this->addNewHuman();
    }
    if (this->getNumberOfOrganisms() < LIMIT_OF_ORGANISMS && round < LIMIT_OF_ORGANISMS) {
        this->addNewOrganism();
    }
    for (auto organism : organismsAlive) {
        Plant* plant = dynamic_cast<Plant*>(organism);
        if (plant != nullptr) {
            plant->changeBreed();
        }
    }
    communicates.clear();
    for (int i = 0; i < organismsAlive.size(); i++) {
        mvprintw(WORLD_Y+5, 2, "To save press key '%c'", SAVE_CHAR);
        mvprintw(13, WORLD_X+2, "%d rounds left to activate special potion!", this->roundsLeftToActivatePotion);
        organismsAlive[i]->setAge(organismsAlive[i]->getAge()+1);
        Human* humanPtr = dynamic_cast<Human*>(organismsAlive[i]);
        if (humanPtr != nullptr && organismsAlive[i]->getX() >= 135 && organismsAlive[i]->getY() >= 35) {
            organismsAlive[i]->setPosition(0, 0);
        }
        if (humanPtr != nullptr) {
            if (humanPtr->isPotionActive()) {
                mvprintw(12, WORLD_X+2, "HUMAN'S MAGIC POTION IS ACTIVE");
                if (humanPtr->returnStrength() > HUMAN_STRENGTH) humanPtr->decreaseMagicPotion();
                if (humanPtr->isPotionActive() && humanPtr->returnStrength() == HUMAN_STRENGTH) {
                    humanPtr->deactivePotion();
                    this->roundsLeftToActivatePotion = 6;
                }
            }
            if(roundsLeftToActivatePotion > 0) this->roundsLeftToActivatePotion--;
            mvprintw(5, WORLD_X+2, "Current Coordinates of Human: (%d, %d)", organismsAlive[i]->getX(), organismsAlive[i]->getY());     
        }
        //if (humanPtr == nullptr) {
        this->moveEveryOrganism(organismsAlive[i]);
        //}

        int rows, cols;
        getmaxyx(stdscr, rows, cols);
        rows = WORLD_Y;
        cols = WORLD_X;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                attron(COLOR_PAIR(1));
                mvaddch(row, col, '+');
                attroff(COLOR_PAIR(1));
            }
        }

        this->displayOrganisms();
        organismsAlive[i]->drawOrganism(map);
        this->drawHowManyOrganisms();
        this->printCommunicates();
    }
    round++;
}

std::vector<int> World::searchForFreeFields(Organism* organism, const int x, const int y) {
    std::vector<int> coords;

    // Check adjacent fields
    int adjX[] = {0, 1, 0, -1};
    int adjY[] = {-1, 0, 1, 0};

    for (int i = 0; i < 4; i++) {
        int newX = x + adjX[i];
        int newY = y + adjY[i];

        if (newX >= 0 && newX < WORLD_X && newY >= 0 && newY < WORLD_Y) {
            Organism* org = this->findOrganism(newX, newY);
            if (org == nullptr) {
                coords.push_back(newX);
                coords.push_back(newY);
                return coords;
            }
        }
    }

    coords.push_back(-1);
    coords.push_back(-1);
    return coords;
}

void World::moveEveryOrganism(Organism* organism) {
    organism->action();
}

void World::drawHowManyOrganisms() {
    mvprintw(2, WORLD_X+2, "%d Organisms Alive.", organismsAlive.size());
}

int World::randomNumber() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int randomNumber = rand() % 101;
    return randomNumber;
}


int World::randomMove() {
    int randomNum = rand() % 4 + 1;
    return randomNum;
}

void World::displayOrganisms() {

    // Draw the map and organisms
    
    for (int i = 0 ; i < organismsAlive.size() ; i++) {
        Human* humanPtr = dynamic_cast<Human*>(organismsAlive[i]);
        if (humanPtr != nullptr) {
            attron(COLOR_PAIR(3));
            mvaddch(organismsAlive[i]->getY(), organismsAlive[i]->getX(), 'H');
            attroff(COLOR_PAIR(3));
            continue;
        }
        else {
            attron(COLOR_PAIR(2));
            mvaddch(organismsAlive[i]->getY(), organismsAlive[i]->getX(), organismsAlive[i]->getSign());
            attroff(COLOR_PAIR(2));
        }
    }

    // Refresh the screen
    //refresh();
}


Organism* World::checkForCollision(Organism* attacker) {
    Organism* victim = findOrganism(attacker->getX(), attacker->getY());
    if (victim != attacker && victim != nullptr) {
        mvprintw(WORLD_Y + 2, 0, "%c stepped on field of %c", attacker->getSign(), victim->getSign());
        return victim;
    }
    return nullptr;
}

Organism* World::checkHumanCollision() {
    Organism* human = nullptr;
    for (Organism* organism : organismsAlive) {
        if (dynamic_cast<Human*>(organism)) {  // check if organism is a Human
            human = organism;
        } 
    }
    for (Organism* organism : organismsAlive) {
        if (organism != human && organism->getX() == human->getX() && organism->getY() == human->getY()) {  // check for collision
            return organism;
        }
    }
    return nullptr;  // no collision
}

bool World::humanAlive() {
    bool humanExist = true;
    for (Organism* organism : organismsAlive) {
        Human* humanPtr = dynamic_cast<Human*>(organism);
        if (humanPtr == nullptr) humanExist = false;
        else {
            humanExist = true;
            break;
        }
    }
    return humanExist;
}

void World::addEverySpecies() {
    Organism* newOrganism = nullptr;

    for (int i = 0; i < 11; i++) {
        std::random_device rd1;
        std::mt19937 gen1(rd1());
        std::uniform_int_distribution<int> dis1(1, WORLD_X-1);

        std::random_device rd2;
        std::mt19937 gen2(rd2());
        std::uniform_int_distribution<int> dis2(1, WORLD_Y-1);
        int x = dis1(gen1);
        int y = dis2(gen2);
        switch (i) {
            case 0:
                newOrganism = new Wolf(x, y, this);
                break;
            case 1:
                newOrganism = new Sheep(x, y, this);
                break;
            case 2:
                newOrganism = new Fox(x, y, this);
                break;
            case 3:
                newOrganism = new Turtle(x, y, this);
                break;
            case 4:
                newOrganism = new Antelope(x, y, this);
                break;
            case 5:
                newOrganism = new Cybersheep(x, y, this);
                break;
            case 6:
                newOrganism = new Grass(x, y, this);
                break;
            case 7:
                newOrganism = new Sowthistle(x, y, this);
                break;
            case 8:
                newOrganism = new Guarana(x, y, this);
                break;
            case 9:
                newOrganism = new Belladonna(x, y, this);
                break;
            case 10:
                newOrganism = new Sosnowskyshogweed(x, y, this);
                break;
        }
        if (newOrganism != nullptr) {
            newOrganism->setWorld(this);
            organismsAlive.push_back(newOrganism);
        }
    }
    sortOrganisms(&organismsAlive);
}


// add a new organism
void World::addNewOrganism() {
    srand(time(nullptr));
    Organism* newOrganism = nullptr;
    int randomNumber = this->randomNumber();
    int x, y;

    this->handleDuplicateCords(&x, &y);
    //mvprintw(WORLD_Y + 2, 0, "NUMBERS: (%d, %d)", this->setRandomX(), this->setRandomY());
    switch (randomNumber / 10) {
        case 0:
            newOrganism = new Wolf(x, y, this);
            break;
        case 1:
            newOrganism = new Sheep(x, y, this);
            break;
        case 2:
            newOrganism = new Fox(x, y, this);
            break;
        case 3:
            newOrganism = new Turtle(x, y, this);
            break;
        case 4:
            newOrganism = new Antelope(x, y, this);
            break;
        case 5:
            newOrganism = new Cybersheep(x, y, this);
            break;
        case 6:
            newOrganism = new Grass(x, y, this);
            break;
        case 7:
            newOrganism = new Sowthistle(x, y, this);
            break;
        case 8:
            newOrganism = new Guarana(x, y, this);
            break;
        case 9:
            newOrganism = new Belladonna(x, y, this);
            break;
        case 10:
            newOrganism = new Sosnowskyshogweed(x, y, this);
            break;
    }
    if (newOrganism != nullptr) {
        newOrganism->setWorld(this);
        organismsAlive.push_back(newOrganism);
        sortOrganisms(&organismsAlive);
    }
}

void World::addNewHuman() {
    Organism* newHuman = new Human(0, 0, this);
    if (newHuman != nullptr) {
        newHuman->setWorld(this);
        organismsAlive.push_back(newHuman);
    }
}

void World::addChild(Organism* organism) {
    organism->setWorld(this);
    organismsAlive.push_back(organism);
    sortOrganisms(&organismsAlive);
}

void World::changeHumanPosition(const int x, const int y) {
    for (int i = 0; i < organismsAlive.size(); i++) {
        Human* humanPtr = dynamic_cast<Human*>(organismsAlive[i]);
        if (humanPtr != nullptr) {
            organismsAlive[i]->setPosition(x, y);
        }
    }
}

void World::changePrevHumanPosition(const int x, const int y) {
    for (int i = 0; i < organismsAlive.size(); i++) {
        Human* humanPtr = dynamic_cast<Human*>(organismsAlive[i]);
        if (humanPtr != nullptr) {
            humanPtr->setPrevPos(x, y);
        }
    }
}

void World::activeMagicPotion() {
    if (this->roundsLeftToActivatePotion > 0) return;
    for (Organism* organism : organismsAlive) {
        Human *humanPtr = dynamic_cast<Human*>(organism);
        if (humanPtr != nullptr) humanPtr->magicPotion();
    }
}

Human* World::getHuman() const {
    for (int i = 0 ; i < organismsAlive.size() ; i++) {
        Human* humanPtr = dynamic_cast<Human*>(organismsAlive[i]);
        if (humanPtr != nullptr) return humanPtr;
    }
    return nullptr;
}

void World::sortOrganisms(std::vector<Organism*> *organisms) {
    std::sort(organisms->begin(), organisms->end(), [](const Organism* a, const Organism* b) {
        if (a->getInitiative() == b->getInitiative()) {
            return a->getAge() > b->getAge();
        }
        return a->getInitiative() > b->getInitiative();
    });
}

bool World::compareOrganisms(const Organism* a, const Organism* b) {
    if (a->getInitiative() == b->getInitiative()) {
        return a->getAge() > b->getAge();
    }
    return a->getInitiative() > b->getInitiative();
}

void World::removeOrganism(Organism* victim, Organism *attacker) {
    if (victim->getSign() == attacker->getSign()) return;
    this->addCommunicate(std::string(1, attacker->getSign()) + " killed " + std::string(1, victim->getSign()));
    for (auto it = organismsAlive.begin(); it != organismsAlive.end(); ++it) {
        if (*it == victim) {
            organismsAlive.erase(it);
            return;
        }
    }

}

int World::setRandomX() {
    int randomInt = rand() % 122 + 2;
    return randomInt;
}

int World::setRandomY() {
    int randomInt = rand() % 32 + 2;
    return randomInt;
}

void World::handleDuplicateCords(int *x, int *y) {
    bool isUsed;
    *x = setRandomX();
    *y = setRandomY();
    for (int i = 0; i < organismsAlive.size(); i++) {
        if (organismsAlive[i]->getX() == *x && organismsAlive[i]->getY() == *y) {
            *x = setRandomX();
            *y = setRandomY();
            i = 0;
        }
    }
}

void World::moveTo(const int x, const int y, const int distance, Organism* organism, World* world, const int prevX, const int prevY) {
    organism->setPosition(x, y);
}

void World::printOrganisms() {
    for (int i = 0; i < organismsAlive.size(); i++) {
        mvprintw(WORLD_Y + i + 3, 40, "%c - COORDINATES: (%d, %d)",organismsAlive[i]->getSign() ,organismsAlive[i]->getX(), organismsAlive[i]->getY());
    }
}

void World::setCybersheepsCount() {
    this->cybersheepsCount++;
}


int World::returnCybersheepsCount() const {
    return this->cybersheepsCount;
}

void World::addCommunicate(std::string str) {
    communicates.push_back(str);
}

void World::printCommunicates() {
    for (int i = 0 ; i < communicates.size() ; i++) {
        mvprintw(15+i, WORLD_X+2, "%s", communicates.at(i).c_str());
    }
}

void World::saveTheGame() {
    clear(); // clear the screen
    refresh(); // refresh the screen to update changes
    char filename[100];
    printw("Enter the filename to save the game: ");
    echo(); // enable echo mode
    keypad(stdscr, true); // enable keypad
    getstr(filename); // get user input
    //noecho(); // disable echo mode
    //keypad(stdscr, false); // disable keypad
    std::string filepath = "gameSaves/" + std::string(filename);
    std::ofstream FILE(filepath);

    FILE << organismsAlive.size();
    FILE << "\n";
    FILE << round;
    FILE << "\n";
    FILE << roundsLeftToActivatePotion;
    FILE << "\n";
    FILE << cybersheepsCount;
    FILE << "\n";

    for (auto organism : organismsAlive) {
        organism->saveOrganism(organism, FILE);
    }
    FILE.close();
    Human* humanPtr = this->getHuman();
    //humanPtr->loop = 'q';
    //this->makeTurn();
}

void World::loadTheGame() {
    clear();
    refresh();

    // Open gameSaves directory
    DIR *dir;
    struct dirent *ent;
    std::string dirName = "gameSaves/";
    if ((dir = opendir(dirName.c_str())) != NULL) {
        // Print each file in the directory and store them in a vector
        std::vector<std::string> files;
        printw("Select a file to load:\n");
        while ((ent = readdir(dir)) != NULL) {
            std::string filename = ent->d_name;
            if (filename == "." || filename == "..") {
                continue;
            }
            // Add the filename to the vector
            files.push_back(filename);
            // Print the filename
            printw("- %s\n", filename.c_str());
        }
        closedir(dir);

        // Wait for the user to choose a file
        printw("\nType the number of the file you want to load: ");
        refresh();
        int choice = getch() - '0';
        while (choice <= 0 || choice > files.size()) {
            printw("\nInvalid choice. Please enter a number between 1 and %d: ", files.size());
            refresh();
            choice = getch() - '0';
        }

        // Return the selected filename
        std::string selectedFile = dirName + files[choice - 1];
        organismsAlive.clear();
        communicates.clear();
        this->fileData(selectedFile);
    } else {
        // Failed to open directory
        printw("Failed to open gameSaves directory.\n");
    }

}


void World::fileData(std::string filename) {
    int howManyOrganisms, cybersheepsCountCp, roundCp, roundsLeftToActivatePotionCp;
    std::ifstream FILE(filename);
    FILE >> howManyOrganisms;
    FILE >> this->round;
    FILE >> this->roundsLeftToActivatePotion;
    FILE >> this->cybersheepsCount;
    for (int i = 0 ; i < howManyOrganisms ; i++) {
        this->loadSavedOrganism(FILE);
    }
}

void World::loadSavedOrganism(std::ifstream &FILE) {
    
    std::string line;
    if (std::getline(FILE, line)) {
        std::istringstream iss(line);
        char sign = ' ', delimiter;
        int xCp, yCp, strengthCp;
        iss >> sign >> delimiter >> xCp >> delimiter >> yCp >> delimiter >> strengthCp;
        Organism* organism = nullptr;
        switch (sign) {
            case HUMAN_SIGN:
                organism = new Human(xCp, yCp, this, strengthCp);
                break;
            case ANTELOPE_SIGN:
                organism = new Antelope(xCp, yCp, this, strengthCp);
                break;
            case BELLADONNA_SIGN:
                organism = new Belladonna(xCp, yCp, this);
                break;
            case CYBERSHEEP_SIGN:
                organism = new Cybersheep(xCp, yCp, this, strengthCp);
                break;
            case FOX_SIGN:
                organism = new Fox(xCp, yCp, this, strengthCp);
                break;
            case GRASS_SIGN:
                organism = new Grass(xCp, yCp, this);
                break;
            case GUARANA_SIGN:
                organism = new Guarana(xCp, yCp, this);
                break;
            case SHEEP_SIGN:
                organism = new Sheep(xCp, yCp, this, strengthCp);
                break;
            case SOSNOWSKY_SIGN:
                organism = new Sosnowskyshogweed(xCp, yCp, this);
                break;
            case SOWTHISTLE_SIGN:
                organism = new Sowthistle(xCp, yCp, this);
                break;
            case TURTLE_SIGN:
                organism = new Turtle(xCp, yCp, this, strengthCp);
                break;
            case WOLF_SIGN:
                organism = new Wolf(xCp, yCp, this, strengthCp);
                break;
        }
        if (organism != nullptr) {
            organism->setWorld(this);
            organismsAlive.push_back(organism);
            sortOrganisms(&organismsAlive);
        }
    }
}

bool World::gameOver() const {
    return endTheGame;
}

void World::setGameOver(bool end) {
    this->endTheGame = end;
}
