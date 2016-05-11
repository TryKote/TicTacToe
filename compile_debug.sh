#!/bin/bash
g++ -Wall -fexceptions -g -std=c++11 -Iinclude -c main.cpp -o obj/Debug/main.o
g++ -Wall -fexceptions -g -std=c++11 -Iinclude -c src/area.cpp -o obj/Debug/src/area.o
g++ -Wall -fexceptions -g -std=c++11 -Iinclude -c src/tcore.cpp -o obj/Debug/src/tcore.o
g++  -o bin/Debug/TicTacToe obj/Debug/main.o obj/Debug/src/area.o obj/Debug/src/tcore.o  -lncurses -lpthread  