#include <iostream>
#include <ncurses.h>
#include <cstring>
#include "area.h"
#include "tcore.h"

using namespace std;



int main()
{
    area tictactoe;
    initscr();
    start_color();
    init_pair (1, COLOR_WHITE, COLOR_RED); //red text, black background
    unsigned int maxX, maxY;
    const char* msg = "TicTacToe";
    box(stdscr, '|', '-');
    getmaxyx(stdscr, maxY, maxX);
    attron(COLOR_PAIR(1));
    attron(A_BOLD);
    mvwprintw(stdscr, 1, (maxX-strlen(msg))/2, msg);
    attroff(COLOR_PAIR(1));
    attroff(A_BOLD);
    tcore game(tictactoe.getMap(), maxX, maxY);
    game.play(); //this is the game
    //getch();
    endwin();
    return 0;
}
