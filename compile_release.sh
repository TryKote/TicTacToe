#!/bin/bash
g++ -Wall -fexceptions -O2 -std=c++11 -Iinclude -c main.cpp -o obj/Release/main.o
g++ -Wall -fexceptions -O2 -std=c++11 -Iinclude -c src/area.cpp -o obj/Release/src/area.o
g++ -Wall -fexceptions -O2 -std=c++11 -Iinclude -c src/tcore.cpp -o obj/Release/src/tcore.o
g++  -o bin/Release/TicTacToe obj/Release/main.o obj/Release/src/area.o obj/Release/src/tcore.o  -s -lncurses -lpthread  