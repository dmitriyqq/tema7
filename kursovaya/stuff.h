//
// Created by dima on 09.03.18.
//

#ifndef KURSOVAYA_STUFF_H
#define KURSOVAYA_STUFF_H

#include <algorithm>
#include <iostream>

const int NUM_SHIFTS = 500;

const int WIDTH = 4;
const int HEIGHT =  4;
const int SIZE = WIDTH * HEIGHT;


const char win[SIZE] = {1, 2, 3, 4, 5 ,6 ,7 , 8, 9, 10, 11, 12, 13, 14, 15, '*'};


enum Move{NOPE=0, UP = 1, RIGHT = 2, DOWN = 3, LEFT = 4};

extern const char win[SIZE];

void debug(const char array[], int depth);

void debugScore( int depth, int score);
void debugMove( int depth, char* move);

void applyMove( char* array, Move move);

bool checkWin(const char* array);

bool checkPos(const char* array, const char* ref);

char* getWinArray();

char*  getRandomArray();

#endif //KURSOVAYA_STUFF_H
