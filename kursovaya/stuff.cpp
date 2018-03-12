//
// Created by dima on 09.03.18.
//

#include <vector>
#include "stuff.h"

void swap(char * array, int i, int j){
    char t = array[i];
    array[i] = array[j];
    array[j] = t;
}

void debug(const char array[], int depth){
    for(int i = 0; i < HEIGHT; i++){
        for(int i = 0; i < depth; i++)
            std::cout<<"    ";
        for(int j = 0; j < WIDTH; j++){
            char c = array[i*WIDTH + j];
            c != '*' ? putchar(c > 9 ? c + 'a' - 10 : c +'0') : putchar(c);
        }

        putchar('\n');
    }
}


void debugScore( int depth, int score){

    for(int i = 0; i < depth; i++)
        std::cout<<"    ";
    printf("depth=%dscore=%d\n", depth, score);

}

void debugMove( int depth, char * name){

    for(int i = 0; i < depth; i++)
        std::cout<<"    ";
    printf("depth=%dmove=%5s\n", depth, name);

}

void applyMove( char* array, Move move){
    int star_i = 0, star_j = 0;
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            if(array[i*WIDTH + j] == '*') {
                star_i = i;
                star_j = j;
            }
        }
    }

    switch(move){
        case UP:
            if(star_i != HEIGHT-1) {
                swap(array, star_i*WIDTH + star_j, (star_i+1)*WIDTH + star_j);
            }
            break;
        case DOWN:
            if(star_i != 0) {
                swap(array, star_i*WIDTH + star_j, (star_i-1)*WIDTH + star_j);
            }
            break;
        case LEFT:
            if(star_j != WIDTH-1) {
                swap(array, star_i*WIDTH + star_j, star_i*WIDTH + star_j+1);
            }
            break;
        case RIGHT:
            if(star_j != 0) {
                swap(array, star_i*WIDTH + star_j, star_i*WIDTH + star_j-1);
            }
            break;
    }
}

bool checkWin(const char* array){
    for(int i = 0; i < SIZE; i++){
        if(array[i] != win[i]) return false;
    }
    return true;
}

bool checkPos(const char* array, const char* ref){
    for(int i = 0; i < SIZE; i++){
        if(ref[i] != '*')
            if(array[i] != ref[i]) return false;
    }
    return true;
}

char* getWinArray(){
    auto array = new char[SIZE];
    for(int i = 0; i < SIZE; i++){
        array[i] = win[i];
    }
    return array;
}

char*  getRandomArray(){
    char *array = getWinArray();

    for(int i = 0; i < NUM_SHIFTS; i++){
        int move = 1 + rand()%4;
        applyMove(array, static_cast<Move>(move));
    }

    return array;
}