#include <random>
#include <cstring>
#include "tcore.h"

//Where drow play-area:
#define SQUARE_X 5
#define SQUARE_Y 3

//Debug switcher
#define DEBUG 0

//Method of solving difficult situations:
#define METHOD 1 //1 -- element of random; 0 -- serial listing

tcore::tcore(cell **input, unsigned int sizex, unsigned int sizey) {
    floor = input;
    deadheat = false;
    maxX = sizex;
    maxY = sizey;
}

void tcore::setColorNormal() {
    init_pair (2, COLOR_WHITE, COLOR_BLACK);
    attrset(COLOR_PAIR(1));
}

win tcore::isGameOver() {
    win flag;

    flag.isGameOver = true;
    int howIsEmpty = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (floor[i][j].empty) howIsEmpty++;
    if (howIsEmpty == 0)  {
        deadheat = true;
        return flag;
    }

    flag.isGameOver = false;

    for (int i = 0; i < 3; i++) {
        if (!floor[i][0].empty && !floor[i][1].empty && !floor[i][2].empty) //vertical lines
            if ((floor[i][0].value == floor[i][1].value) && (floor[i][1].value == floor[i][2].value)) {
                flag.isGameOver = true;
                flag.whoWin = floor[i][0].value;
                return flag;
            }

        if (!floor[0][i].empty && !floor[1][i].empty && !floor[2][i].empty) //horizontal lines
            if ((floor[0][i].value == floor[1][i].value) && (floor[1][i].value == floor[2][i].value)) {
                flag.isGameOver = true;
                flag.whoWin = floor[0][i].value;
                return flag;
            }
    }
    if (!floor[0][0].empty && !floor[1][1].empty && !floor[2][2].empty) {//general diagonal
        if ((floor[0][0].value == floor[1][1].value) && (floor[1][1].value == floor[2][2].value)) {
            flag.isGameOver = true;
            flag.whoWin = floor[0][0].value;
            return flag;
        }
    }
    if (!floor[2][0].empty && !floor[1][1].empty && !floor[0][2].empty) //secondary diagonal
        if ((floor[2][0].value == floor[1][1].value) && (floor[1][1].value == floor[0][2].value)) {
            flag.isGameOver = true;
            flag.whoWin = floor[2][0].value;
            return flag;
        }

    return flag;
}

chtype tcore::CellToChar(cell some) {
    if (some.empty) return ' ';
    if (some.value) return 'X';
    else return '0';
}

void tcore::drowOnSquare(int x, int y, cell **map) {
    curs_set(0);
    int currenMapY = 0;
    move(y,x);
    for (int i = 0; i < 3; i++) {
        addch('|');
        addch(CellToChar(map[i][currenMapY]));
        if (i == 2) addch('|');
    }
    currenMapY++;
    move(y+1, x);
    for (int i = 0; i < 3; i++) {
        addch('|');
        addch(CellToChar(map[i][currenMapY]));
        if (i == 2) addch('|');
    }
    currenMapY++;
    move(y+2, x);
    for (int i = 0; i < 3; i++) {
        addch('|');
        addch(CellToChar(map[i][currenMapY]));
        if (i == 2) addch('|');
    }
    refresh();
}

bool tcore::step() {
    refresh();
    bool stepIsOver = false;

    cell setzero;
    setzero.empty = false;
    setzero.value = false;

    srand(time(NULL));
    int howIsEmpty = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (floor[i][j].empty) howIsEmpty++;

    if (DEBUG) mvprintw(18,10,"Empty cells: %d", howIsEmpty);

    if (floor[1][1].empty) {
        floor[1][1] = setzero;
        if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",1,1);
        stepIsOver = true;
        return 1;
    }

    if (floor[0][0].empty) {
        if (((!floor[0][1].empty && !floor[0][2].empty) && (floor[0][1].value == floor[0][1].value)) || ((!floor[1][1].empty && !floor[2][2].empty) && (floor[1][1].value == floor[2][2].value))) {
            floor[0][0] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",0,0);
            stepIsOver = true;
            return 1;
        }
        if ((!floor[1][0].empty && !floor[2][0].empty) && (floor[1][0].value == floor[2][0].value))  {
            floor[0][0] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",0,0);
            stepIsOver = true;
            return 1;
        }
    }
    if (floor[1][0].empty) {
        if ((!floor[0][0].empty && !floor[2][0].empty) && (floor[0][0].value == floor[2][0].value)) {
            floor[1][0] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",1,0);
            stepIsOver = true;
            return 1;
        }
        if ((!floor[1][1].empty && !floor[1][2].empty) && (floor[1][1].value == floor[1][2].value)) {
            floor[1][0] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",1,0);
            stepIsOver = true;
            return 1;
        }
    }
    if (floor[2][0].empty) {
        if ((!floor[0][0].empty && !floor[1][0].empty) && (floor[0][0].value == floor[1][0].value)) {
            floor[2][0] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",2,0);
            stepIsOver = true;
            return 1;
        }
        if ((!floor[2][1].empty && !floor[2][2].empty) && (floor[2][1].value == floor[2][2].value)) {
            floor[2][0] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",2,0);
            stepIsOver = true;
            return 1;
        }
        if ((!floor[1][1].empty && !floor[0][2].empty) && (floor[1][1].value == floor[0][2].value)) {
            floor[2][0] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",2,0);
            stepIsOver = true;
            return 1;
        }
    }
    if (floor[0][1].empty) {
        if ((!floor[0][0].empty && !floor[0][2].empty) && (floor[0][0].value == floor[0][2].value)) {
            floor[0][1] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",0,1);
            stepIsOver = true;
            return 1;
        }
        if ((!floor[1][1].empty && !floor[2][1].empty) && (floor[1][1].value == floor[2][1].value)) {
            floor[0][1] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",0,1);
            stepIsOver = true;
            return 1;
        }
    }
    if (floor[1][1].empty) {
        if ((!floor[1][0].empty && !floor[1][2].empty) && (floor[1][0].value == floor[1][2].value)) {
            floor[1][1] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",1,1);
            stepIsOver = true;
            return 1;
        }
        if ((!floor[1][0].empty && !floor[1][2].empty) && (floor[1][0].value == floor[1][2].value)) {
            floor[1][1] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",1,1);
            stepIsOver = true;
            return 1;
        }
        if ((!floor[0][0].empty && !floor[2][2].empty) && (floor[0][0].value == floor[2][2].value)) {
            floor[1][1] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",1,1);
            stepIsOver = true;
            return 1;
        }
        if ((!floor[2][0].empty && !floor[0][2].empty) && (floor[2][0].value == floor[0][2].value)) {
            floor[1][1] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",1,1);
            stepIsOver = true;
            return 1;
        }
    }
    if (floor[2][1].empty) {
        if ((!floor[2][0].empty && !floor[2][2].empty) && (floor[2][0].value == floor[2][2].value)) {
            floor[2][1] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",2,1);
            stepIsOver = true;
            return 1;
        }
        if ((!floor[0][1].empty && !floor[1][1].empty) && (floor[0][1].value == floor[1][1].value)) {
            floor[2][1] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",2,1);
            stepIsOver = true;
            return 1;
        }
    }
    if (floor[0][2].empty) {
        if ((!floor[0][0].empty && !floor[0][1].empty) && (floor[0][0].value == floor[0][1].value)) {
            floor[0][2] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",0,2);
            stepIsOver = true;
            return 1;
        }
        if ((!floor[1][2].empty && !floor[2][2].empty) && (floor[1][2].value == floor[2][2].value)) {
            floor[0][2] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",0,2);
            stepIsOver = true;
            return 1;
        }
        if ((!floor[2][2].empty && !floor[2][0].empty) && (floor[2][2].value == floor[2][0].value)) {
            floor[0][2] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",0,2);
            stepIsOver = true;
            return 1;
        }
    }
    if (floor[1][2].empty) {
        if ((!floor[1][0].empty && !floor[1][1].empty) && (floor[1][0].value == floor[1][1].value)) {
            floor[1][2] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",1,2);
            stepIsOver = true;
            return 1;
        }
        if ((!floor[0][2].empty && !floor[2][2].empty) && (floor[0][2].value == floor[2][2].value)) {
            floor[1][2] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",1,2);
            stepIsOver = true;
            return 1;
        }
    }
    if (floor[2][2].empty) {
        if ((!floor[0][2].empty && !floor[1][2].empty) && (floor[0][2].value == floor[1][2].value)) {
            floor[2][2] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",2,2);
            stepIsOver = true;
            return 1;
        }
        if ((!floor[2][0].empty && !floor[2][1].empty) && (floor[2][0].value == floor[2][1].value)) {
            floor[2][2] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",2,2);
            stepIsOver = true;
            return 1;
        }
        if ((!floor[0][0].empty && !floor[1][1].empty) && (floor[0][0].value == floor[1][1].value)) {
            floor[2][2] = setzero;
            if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",2,2);
            stepIsOver = true;
            return 1;
        }
    }

    switch(METHOD) { //Method of solving difficult situations
    case 0: //serial listing
        if (!stepIsOver)
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    if (floor[i][j].empty) {
                        floor[i][j].empty = false;
                        floor[i][j].value = false;
                        if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",i,j);
                        stepIsOver = true;
                        return 1;
                    }
        break;
    case 1: //with random
        while(!stepIsOver) {
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++) {
                    int temprandom = rand()%(howIsEmpty+1);
                    if ((temprandom == 0) && (floor[i][j].empty)) {
                        floor[i][j].empty = false;
                        floor[i][j].value = false;
                        if (DEBUG) mvprintw(15,10, "Step go on (%d;%d)",i,j);
                        stepIsOver = true;
                        return 1;
                    }
                }
        }
        break;
    }

    drowOnSquare(SQUARE_X, SQUARE_Y, this->floor);
    return stepIsOver;
}

void tcore::play() {
    int curX = SQUARE_X+1, curY = SQUARE_Y; //in floor on X:0, Y:0
    int curX_onFloor = 0, curY_onFloor = 0;
    int iterator = 0;
    //getyx(stdscr, curY, curX);


    while (!this->isGameOver().isGameOver) {
        keypad(stdscr, true);

        while(true) {
            //DEBUG CNT:
            iterator++;
            if (DEBUG) mvprintw(19, 10, "Curs on floor is (%d;%d)", curX_onFloor, curY_onFloor);
            if (DEBUG) mvprintw(20, 10, "Iteration: %d", iterator);
            if (DEBUG) mvprintw(22, 10, "Curs pos now is (%d;%d)", curX, curY);

            drowOnSquare(SQUARE_X, SQUARE_Y, this->floor);
            move(curY, curX);
            curs_set(1); //debug
            int tempkey = getch();
            switch(tempkey) {
            case KEY_LEFT:
                if (DEBUG) mvprintw(21, 10, "Key pressed: %d", tempkey);
                move(curY, curX);
                if (curX > SQUARE_X+1) {
                    curX = curX - 2; //jump through separators
                    curX_onFloor--;
                }
                break;
            case KEY_RIGHT:
                if (DEBUG) mvprintw(21, 10, "Key pressed: %d", tempkey);
                move(curY, curX);
                if (curX < SQUARE_X+5) {
                    curX = curX + 2; //jump through separators
                    curX_onFloor++;
                }
                break;
            case KEY_UP:
                if (DEBUG) mvprintw(21, 10, "Key pressed: %d", tempkey);
                move(curY, curX);
                if (curY > SQUARE_Y) {
                    curY--;
                    curY_onFloor--;
                }
                break;
            case KEY_DOWN:
                if (DEBUG) mvprintw(21, 10, "Key pressed: %d", tempkey);
                move(curY, curX);
                if (curY < SQUARE_Y+2) {
                    curY++;
                    curY_onFloor++;
                }
                break;
            case 32: //SPACE

                if (floor[curX_onFloor][curY_onFloor].empty) {
                    if (DEBUG) mvprintw(17,10, "Cell (%d;%d) is empty", curX_onFloor, curY_onFloor);
                    floor[curX_onFloor][curY_onFloor].empty = false;
                    floor[curX_onFloor][curY_onFloor].value = true;
                    drowOnSquare(SQUARE_X, SQUARE_Y, this->floor);
                    //getch();
                    if (!this->isGameOver().isGameOver)
                        if(this->step()) {
                            if (DEBUG) mvprintw(16,10,"Step ++");
                        } else {
                            if (DEBUG) mvprintw(15,10, "Step go on (-;-)");
                            if (DEBUG) mvprintw(16,10,"Step --");
                        }
                    drowOnSquare(SQUARE_X, SQUARE_Y, this->floor);

                }
                break;
                /*default:
                    if (DEBUG) mvprintw(21, 10, "Key pressed: %d", tempkey);
                    move(curY, curX);*/
            }

            if (!this->isGameOver().isGameOver) {
                //mvprintw(6,6, "Game NOT over!");
            } else {
                //clear();
                curs_set(0);
                if (!deadheat) {
                    if (this->isGameOver().whoWin) {
                        move (6,6);
                        msg = "Crosses wins!";
                        attron(A_BOLD);
                        init_pair (3, COLOR_GREEN, COLOR_BLACK);
                        attron(COLOR_PAIR(3));
                        mvprintw((maxY/2), (maxX-strlen(msg))/2, msg);
                        setColorNormal();
                        refresh();
                        getch();
                    } else {
                        move (6,6);
                        msg = "Zeros wins!";
                        attron(A_BOLD);
                        init_pair (3, COLOR_RED, COLOR_BLACK);
                        attron(COLOR_PAIR(3));
                        mvprintw((maxY/2), (maxX-strlen(msg))/2, msg);
                        setColorNormal();
                        refresh();
                        getch();
                    }
                } else {
                    move (6,6);
                    msg = "Dead heat!";
                    attron(A_BOLD);
                    init_pair (3, COLOR_YELLOW, COLOR_BLACK);
                    attron(COLOR_PAIR(3));
                    mvprintw((maxY/2), (maxX-strlen(msg))/2, msg);
                    setColorNormal();
                    refresh();
                    getch();
                }
                break;
            }

        }

    }
}

tcore::~tcore() {
    //dtor
}
