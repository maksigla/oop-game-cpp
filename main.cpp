#include "world.h"
#include "libs.h"

int main() {
    World newWorld;

    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Set up color pairs
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);

    // Initialize cursor position
    int y = 0;
    int x = 0;

    // Loop until the user presses 'q'
    int ch;
    int previousKey;

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
    newWorld.setMapPlace(x, y, 'H');   
    Human* humanPtr = newWorld.getHuman();

    do {
        // Clear the screen
        clear();
        newWorld.makeTurn();        
        newWorld.displayOrganisms();
        refresh();

    } while (humanPtr->loop != 'q' && !newWorld.gameOver());

    // Clean up ncurses
    endwin();

    return 0;
}
