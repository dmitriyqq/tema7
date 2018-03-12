#include <cstring>
#include <climits>
#include <vector>
#include "iostream"
#include "stuff.h"

const int max_level = 16;

char move_names[][6] = {
        "nope",
        "up",
        "right",
        "down",
        "left"
};

int array_depth[81];

void getStart(char c, int &x, int &y){
    if(c != '*'){
        int cc = c - 1;
        y = (cc/WIDTH);
        x = (cc%WIDTH);
    }else{
        x = 3;
        y = 3;
    }
}


void getStar(char* array, int &x, int &y){
    for(int i = 0; i < SIZE; i++){
        if(array[i] == '*'){
            x = i%WIDTH;
            y = i/WIDTH;
            return;
        }
    }
}


int calcScore(const char *array){
  int score = 0;
  for(int i = 0; i < SIZE; i++){
       int x, y;
       getStart(array[i], x, y);
       int ii = i/WIDTH;
       int jj = i%WIDTH;
       int dx = abs(x - jj);
       int dy = abs(y -ii);
       score += (dx+dy);
      if((dx+dy) == 0){
          score-= 5*(1<<(SIZE-i));
      }
  }

    return score;
}



int solve_dfs(char *array, int depth, Move last, std::vector <Move> & move){
    //std::cout<<"solve d = "<<depth<<std::endl;

    int star_i, star_j;
    //debug(array, depth);
    getStar(array, star_j, star_i);

    Move best = NOPE;

    if(depth == max_level){
        int score = calcScore(array);
        //debugScore(depth, score);
        return score;
    }else {
        int min_score = calcScore(array), current_score = 0;
        std::vector <Move> passup, passdown, passright, passleft;

        if(last != DOWN && star_i != HEIGHT - 1) {
            auto arrayUp = new char[SIZE];
            memcpy(arrayUp, array, SIZE * sizeof(char));
            applyMove(arrayUp, UP);

            current_score = solve_dfs(arrayUp, depth + 1, UP, passup);
            if (current_score < min_score) {
                best = UP;
                min_score = current_score;
            }
            free(arrayUp);
        }
        if(last != UP && star_i != 0) {
            auto arrayDown  = new char[SIZE];
            memcpy(arrayDown, array, SIZE * sizeof(char));
            applyMove(arrayDown, DOWN);

            array_depth[depth] = 1;
            current_score = solve_dfs(arrayDown, depth+1, DOWN, passdown);
            if(current_score < min_score){
                best = DOWN;
                min_score = current_score;
            }
            free(arrayDown);
        }

        if(last != RIGHT && star_j != WIDTH - 1) {
            auto arrayLeft  = new char[SIZE];
            memcpy(arrayLeft, array, SIZE * sizeof(char));
            applyMove(arrayLeft, LEFT);

            current_score = solve_dfs(arrayLeft, depth+1, LEFT, passleft);
            if(current_score < min_score){
                best = LEFT;
                min_score = current_score;
            }
            free(arrayLeft);
        }

        if(last != LEFT && star_j != 0) {
            auto arrayRight = new char[SIZE];
            memcpy(arrayRight, array, SIZE * sizeof(char));
            applyMove(arrayRight, RIGHT);

            current_score = solve_dfs(arrayRight, depth+1, RIGHT, passright);
            if(current_score < min_score){

                best = RIGHT;
                min_score = current_score;
            }

            free(arrayRight);
        }

       // debugMove(depth, move_names[best]);
        switch (best){
            case UP:
                move.push_back(best);
                move.insert(move.end(), passup.begin(), passup.end());
                break;
            case DOWN:
                move.push_back(best);
                move.insert(move.end(), passdown.begin(), passdown.end());
                break;
            case LEFT:
                move.push_back(best);
                move.insert(move.end(), passleft.begin(), passleft.end());
                break;
            case RIGHT:
                move.push_back(best);
                move.insert(move.end(), passright.begin(), passright.end());
                break;
        }

        //debugScore(depth, min_score);
        return min_score;
    }

}



int main(){
    srand(time(0));
    int hod = 0;
    std::cout<<"hod = "<<hod<<std::endl;
    char *array = getRandomArray();

    Move lastmove = NOPE;
    while(1){


        std::vector <Move> moves;
        solve_dfs(array, 0, lastmove, moves);
        if(!moves.size()){
            for(int i = 0; i < 10; i++)
                moves.push_back(static_cast<Move>(1 + rand()%4));
        }
        std::cout<<"num_moves="<<moves.size()<<std::endl;
        for(auto &e: moves){
            std::cout<<move_names[e]<<std::endl;
            applyMove(array, e);
        }

        lastmove = moves[0];

        debug(array, 0);


        if(checkWin(array)){
            printf("Congrats u re winner! Totol %d moves.\n", hod);
            break;
        }

        hod+=moves.size();

    }
    return 0;

}