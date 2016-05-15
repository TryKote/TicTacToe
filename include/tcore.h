#ifndef TCORE_H
#define TCORE_H

#include <ncurses.h>
#include "area.h"

struct win {
    bool isGameOver;
    bool whoWin;
};

class tcore {
public:
    tcore(cell **input, unsigned int sizex, unsigned int sizey);
    ~tcore();
    win isGameOver();
    void play();
    void play(int x, int y);

protected:

private:
    cell **floor;
    chtype CellToChar(cell some);
    void drowOnSquare(int x, int y, cell **map);
    bool deadheat = false;
    bool step();
    const char* msg = new char[20];
    unsigned int maxX, maxY;
    void setColorNormal();
};

#endif // TCORE_H
