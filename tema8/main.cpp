
#include <bits/stdc++.h>

using namespace std;

constexpr int num_words = 8;
int maxget = 0;
char bestgrid[1000][1000];

char words[num_words][16] = {
        "steam",
        "wistful",
        "sharp",
        "ants",
        "fetch",
        "fail",
        "onerous",
        "bake"
};

bool used[num_words];
int words_used = 0;

char grid[1000][1000];

void debug(int depth){
    for(int i = 0; i < 40; i++){
        for(int j = 0; j< depth; j++)
            cout<<"      ";
        for(int j = 0; j < 20; j++){
            cout<<grid[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}

void debugDump(){
    for(int i = 0; i < 40; i++){
        for(int j = 0; j < 20; j++){
            cout<<bestgrid[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}

void dump(){
    for(int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            bestgrid[i][j] = grid[i][j];
        }
    }
}

void solveW(int x, int y, int word, int depth);
void solveH(int x, int y, int word, int depth);

void solveW(int x, int y, int word, int depth){

    int len = strlen(words[word]);
    bool isgood = true;
    char buf[len+1];
    for(int i = 0; i < len; i++){
        buf[i] = grid[y][x+i];
        if(grid[y][x+i] == 0){
            grid[y][x+i] = words[word][i];
        }else if(grid[y][x+i] != words[word][i]){
            isgood = false;
        }
    }

    debug(depth);
    if(isgood) {
        buf[len] = 0;

        used[word] = 1;
        words_used++;

        if(maxget < words_used){
            dump();
            maxget = words_used;
        }

        if (words_used == num_words) {
            debug(0);
            cout<<"FOUND"<<endl;
            exit(0);
        }


        for (int i = 0; i < len; i++) {
            for (int j = 0; j < num_words; j++) {
                if (!used[j]) {
                    int len2 = strlen(words[j]);
                    for (int k = 0; k < len2; k++) {
                        const char *w1 = words[word];
                        const char *w2 = words[j];

                        if (w1[i] == w2[k]) {
                            solveH(x + i, y - k, j,depth+1);
                        }
                    }


                }
            }
        }

        used[word] = 0;
        words_used--;
    }
    for(int i = 0; i < len; i++){
        grid[y][x+i] = buf[i];
    }

}

void solveH(int x, int y, int word, int depth){
    int len = strlen(words[word]);
    char buf[len+1];
    bool isgood = true;
    for(int i = 0; i < len; i++){
        buf[i] = grid[y+i][x];
        if(grid[y+i][x] == 0){
            grid[y+i][x] = words[word][i];
        }else if(grid[y+i][x] != words[word][i]){
            isgood = false;

        }
    }
    if(isgood) {
        debug(depth);
        buf[len] = 0;

        used[word] = 1;
        words_used++;

        if(maxget < words_used){
            dump();
            maxget = words_used;
        }

        if (words_used == num_words) {
            debug(0);
            cout<<"FOUND"<<endl;
            exit(0);
        }


        for (int i = 0; i < len; i++) {
            for (int j = 0; j < num_words; j++) {
                if (!used[j]) {
                    int len2 = strlen(words[j]);
                    for (int k = 0; k < len2; k++) {
                        const char *w1 = words[word];
                        const char *w2 = words[j];

                        if (w1[i] == w2[k]) {
                            solveW(x - k, y + i, j,depth+1);
                        }
                    }
                }
            }
        }

        used[word] = 0;
        words_used--;
    }
    for(int i = 0; i < len; i++){
        grid[y+i][x] = buf[i];
    }
}

int main(){
    solveW(10, 10, 0, 0);
    cout<<"maxget = "<<maxget<<endl;
    debugDump();
}