#include <iostream>
#include <algorithm>
#include <vector>
#include "stuff.h"


int main() {


    char *array = getRandomArray();

    while(1){
        std::string s1;
        std::cin>>s1;
        if(s1 == "up"){
            applyMove(array, UP);
        }else if(s1 == "left"){
            applyMove(array, LEFT);
        }else if(s1 == "right"){
            applyMove(array, RIGHT);
        }else if(s1 == "down"){
            applyMove(array, DOWN);
        }else if(s1 == "exit"){
            break;
        }else{
            std::cout<<"Illegal move"<<std::endl;
        }
        bool w = checkWin(array);
        if(w){
            std::cout<<"Congrats u re winner!"<<std::endl;
        }
        debug(array, 0);
    }
    return 0;
}