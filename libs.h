#include <random>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <utility>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <sstream>

// map dimensions

#define WORLD_Y 35
#define WORLD_X 125

// limit of organisms

#define LIMIT_OF_ORGANISMS 40

// strengths and initiatives for animals

#define HUMAN_STRENGTH 5
#define HUMAN_INITIATIVE 4
#define WOLF_STRENGTH 9
#define WOLF_INITIATIVE 5
#define SHEEP_STRENGTH 4
#define SHEEP_INITIATIVE 4
#define FOX_STRENGTH 3
#define FOX_INITIATIVE 7
#define TURTLE_STRENGTH 2
#define TURTLE_INITIATIVE 1
#define ANTELOPE_STRENGTH 4
#define ANTELOPE_INITIATIVE 4
#define CYBERSHEEP_STRENGTH 11
#define CYBERSHEEP_INITIATIVE 4

// strengths for plants

#define GRASS_STRENGTH 0
#define SOWTHISTLE_STRENGTH 0
#define GUARANA_STRENGTH 0
#define BELLADONNA_STRENGTH 99
#define SOSNOWSKY_STRENGTH 10

// signs for animals and plants

#define HUMAN_SIGN 'H'
#define WOLF_SIGN 'W'
#define SHEEP_SIGN 'S'
#define FOX_SIGN 'F'
#define TURTLE_SIGN 'T'
#define ANTELOPE_SIGN 'A'
#define CYBERSHEEP_SIGN 'C'

#define GRASS_SIGN 'G'
#define SOWTHISTLE_SIGN 'Q'
#define GUARANA_SIGN 'R'
#define BELLADONNA_SIGN 'B'
#define SOSNOWSKY_SIGN 'Y'

#define SAVE_CHAR 's'