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
        void play(int x, int y);

    protected:

    private:
        cell **floor;
        chtype CellToChar(cell some);
        void drowOnSquare(int x, int y, cell **map);
        bool deadheat = false;
        bool step();
};

#endif // TCORE_H
