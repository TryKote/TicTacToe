#include <iostream>
#include <ncurses.h>
#include <cstring>
#include "area.h"
#include "tcore.h"

using namespace std;

chtype CellToChar(cell some) {
    if (some.empty) return ' ';
    if (some.value) return 'X';
    else return '0';
}

void drowOnSquare(int x, int y, cell **map) {
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
}

int main()
{
    area tictactoe;
    cell **N = tictactoe.getMap();
    tcore game(N);
    initscr();
    unsigned int maxX, maxY;
    const char* msg = "TicTacToe";
    box(stdscr, '|', '-');
    getmaxyx(stdscr, maxY, maxX);
    mvwprintw(stdscr, 1, (maxX-strlen(msg))/2, msg);

    tictactoe.set(1,1,1);
    tictactoe.set(1,0,1);
    tictactoe.set(2,0,1);
    drowOnSquare(2,2, N);
    if (game.isGameOver().isGameOver) mvprintw(6,6, "Game over!");

    getch();
    endwin();
    return 0;
}
