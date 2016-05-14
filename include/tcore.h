#ifndef TCORE_H
#define TCORE_H

#include <ncurses.h>
#include "area.h"

struct win{
    bool isGameOver;
    bool whoWin;
};

class tcore
{
    public:
        tcore(cell **input);
        ~tcore();
        win isGameOver();
        void play();

    protected:

    private:
        cell **floor;
        chtype CellToChar(cell some);
        void drowOnSquare(int x, int y, cell **map);
};

#endif // TCORE_H
