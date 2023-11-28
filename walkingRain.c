#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DROPS 700

typedef struct {
    int x, y;
    char symbol;
} Raindrop;

void initRaindrops(Raindrop drops[], int numDrops, int maxCols, int maxRows) {
    srand(time(NULL));
    for (int i = 0; i < numDrops; ++i) {
        drops[i].x = rand() % maxCols;
        drops[i].y = rand() % maxRows;
        drops[i].symbol = '|';
    }
}

void updateRaindrops(Raindrop drops[], int numDrops, int maxRows) {
    for (int i = 0; i < numDrops; ++i) {
        drops[i].y = (drops[i].y + 1) % maxRows;
    }
}

void drawRaindrops(Raindrop drops[], int numDrops) {
    for (int i = 0; i < numDrops; ++i) {
        mvaddch(drops[i].y, drops[i].x, drops[i].symbol);
    }
    refresh();
}

int main() {
    initscr(); 
    noecho();  
    curs_set(FALSE);

    int maxCols, maxRows;
    getmaxyx(stdscr, maxRows, maxCols);

    Raindrop drops[MAX_DROPS];
    initRaindrops(drops, MAX_DROPS, maxCols, maxRows);

    while (1) {
        clear(); // Limpa a tela

        updateRaindrops(drops, MAX_DROPS, maxRows);
        drawRaindrops(drops, MAX_DROPS);

        usleep(100000); 
    }

    endwin(); 
    return 0;
}
