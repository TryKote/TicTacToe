#include "area.h"

area::area()
{
    for (int i = 0; i < 3; i++) {
        floor[i] = new cell[3];
        //for (int j = 0; j < 3; j++) floor[i][j]
    }
}

void area::set(int x, int y, bool val) {
    if (floor[x][y].empty) {
        floor[x][y].empty = false;
        floor[x][y].value = val;
    }
}

cell **area::getMap() {
    return floor;
}

area::~area()
{
    for (int i = 0; i < 3; i++)
        delete floor[i];
    delete[] floor;
}
