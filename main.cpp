#include <iostream>
#include <ncurses.h>
#include <cstring>
#include "area.h"
#include "tcore.h"

using namespace std;



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

    //drowOnSquare(2,2, N);
    //if (game.isGameOver().isGameOver) mvprintw(6,6, "Game over!");
    game.play();

    endwin();
    return 0;
}
