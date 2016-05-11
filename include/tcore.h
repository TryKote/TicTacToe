#ifndef TCORE_H
#define TCORE_H

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

    protected:

    private:
        cell **floor;
};

#endif // TCORE_H
