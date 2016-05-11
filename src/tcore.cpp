#include "tcore.h"

tcore::tcore(cell **input)
{
    floor = input;
}

win tcore::isGameOver() {
    win flag;
    flag.isGameOver = false;

    for (int i = 0; i < 3; i++) {
        if (!floor[i][0].empty && !floor[i][1].empty && !floor[i][2].empty) //vertical lines
            if (floor[i][0].value == floor[i][1].value == floor[i][2].value) {
                flag.isGameOver = true;
                flag.whoWin = floor[i][0].value;
                return flag;
            }

        if (!floor[0][i].empty && !floor[1][i].empty && !floor[2][i].empty) //horizontal lines
            if (floor[0][i].value == floor[1][i].value == floor[2][i].value) {
                flag.isGameOver = true;
                flag.whoWin = floor[0][i].value;
                return flag;
            }
    }
    if (!floor[0][0].empty && !floor[1][1].empty && !floor[2][2].empty) //general diagonal
        if (floor[0][0].value == floor[1][1].value == floor[2][2].value) {
            flag.isGameOver = true;
            flag.whoWin = floor[0][0].value;
            return flag;
        } else
        if (!floor[2][0].empty && !floor[1][1].empty && !floor[0][2].empty) //secondary diagonal
            if (floor[2][0].value == floor[1][1].value == floor[0][2].value) {
                flag.isGameOver = true;
                flag.whoWin = floor[2][0].value;
                return flag;
            }

    return flag;
}

tcore::~tcore()
{
    //dtor
}
