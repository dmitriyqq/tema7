#include <bits/stdc++.h>
using namespace std;
constexpr int num_words = 9;

char words[num_words][16] = {
        "steam",
        "wistful",
        "sharp",
        "ants",
        "fetch",
        "fail",
        "onerous",
        "bake",
        "clever"
};

bool used[num_words];
int words_used = 0;
char grid[1000][1000];
void debug(){
    for(int i = 0; i < 30; i++){
        for(int j = 0; j < 60; j++){
            if(grid[i][j]) cout<<grid[i][j];
            else cout<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}


void solveW(int x, int y, int word);
void solveH(int x, int y, int word);

void solveW(int x, int y, int word){
    int len = strlen(words[word]);
    bool isgood = true;
    char buf[len+1];
    char mask[len+1];
    int connect = 0;
    for(int i = 0; i < len; i++){
        buf[i] = grid[y][x+i];
        if(grid[y][x+i] == 0){
            grid[y][x+i] = words[word][i];
            mask[i] = '*';
        }else if(grid[y][x+i] != words[word][i]){
            isgood = false;

        }else{
            mask[i] = words[word][i];
            connect++;
        }
    }

    for(int i = 0; i < num_words; i++){
        if(i != word && strlen(words[i]) == len){
            int nn = 0;
            for(int j = 0; j < len; j++){
                if(mask[i] != '*'){
                    if(words[i][j] != mask[j]){
                        break;
                    }else{
                       nn++;
                    }
                }
            }
            if(nn == connect){
                isgood = false;
                break;
            }
        }
    }

    if(isgood || !connect) {
        buf[len] = 0;
        used[word] = 1;
        words_used++;
        debug();
        if (words_used == num_words) {
            debug();
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
                            solveH(x + i, y - k, j);
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

void solveH(int x, int y, int word){
    int len = strlen(words[word]);
    char buf[len+1];
    char mask[len+1];
    int connect = 0;
    bool isgood = true;
    for(int i = 0; i < len; i++){
        buf[i] = grid[y+i][x];
        if(grid[y+i][x] == 0){
            grid[y+i][x] = words[word][i];
            mask[i] = '*';
        }else if(grid[y+i][x] != words[word][i]){
            isgood = false;
        }else{
            mask[i] = words[word][i];
            connect++;
        }
    }

    for(int i = 0; i < num_words; i++){
        if(i != word && strlen(words[i]) == len){
            int nn = 0;
            for(int j = 0; j < len; j++){
                if(mask[i] != '*'){
                    if(words[i][j] != mask[j]){
                        break;
                    }else{
                        nn++;
                    }
                }
            }
            if(nn == connect){
                isgood = false;
                break;
            }
        }
    }


    if(isgood  || !connect) {
        buf[len] = 0;
        used[word] = 1;
        words_used++;
        debug();
        if (words_used == num_words) {
            debug();
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
                            solveW(x - k, y + i, j);
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
    solveW(15, 15, 0);
    solveH(15,15, 0);
}