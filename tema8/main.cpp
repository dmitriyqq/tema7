#include <bits/stdc++.h>
using namespace std;

constexpr int grid_width = 1000,
              grid_height = 1000;


int words_used = 0,
    best_score = 0,
        num_words;

char grid[grid_height][grid_width], snapshot[grid_height][grid_width];

void instaExit(){
    int top_y = 0, bot_y = grid_height-1, left_x = 0, right_x = grid_width-1;
    bool end;

    for(end = false; top_y < grid_height; top_y++){
        for(int i = 0; i < grid_width; i++){
            if(snapshot[top_y][i] != 0){
                top_y--;
                end = true;
                break;
            }
        }
        if(end) break;
    }

    for(end = false; bot_y >= 0; bot_y--){
        for(int i = 0; i < grid_width; i++){
            if(snapshot[bot_y][i] != 0){
                bot_y++;
                end = true;
                break;
            }
        }
        if(end) break;
    }

    for(end = false; left_x < grid_width; left_x++){
        for(int i = 0; i < grid_height; i++){
            if(snapshot[i][left_x] != 0){
                left_x--;
                end = true;
                break;
            }
        }
        if(end) break;
    }

    for(end = false; right_x >= 0; right_x--){
        for(int i = 0; i < grid_height; i++){
            if(snapshot[i][right_x] != 0){
                right_x++;
                end = true;
                break;
            }
        }
        if(end) break;
    }

    //cout<<top_y<<" "<<bot_y<<endl;
    //cout<<left_x<<" "<<right_x<<endl;



    for(int i = top_y; i < bot_y; i++){
        for(int j = left_x; j < right_x; j++){
            if(snapshot[i][j]) cout<<snapshot[i][j];
            else cout<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    exit(0);
}

void make_snapshot(){
    for(int i = 0; i < grid_height; i++){
        for(int j = 0; j < grid_width; j++){
            snapshot[i][j] = grid[i][j];
        }
    }

}

int solveW(int x, int y, int word, int score);

int solveH(int x, int y, int word, int score);

vector <string> words;
vector <char>  used;

int solveW(int x, int y, int word, int score){
    int len = (int)(words[word].length());
    bool isgood = true;
    char buf[len+1];
    char mask[len+1];
    int connect = 0;
    for(int i = 0; i < len; i++){
        buf[i] = grid[y][x+i];
        if(grid[y][x+i] == 0 && grid[y+1][x+i] == 0 && grid[y-1][x+i] == 0){
            grid[y][x+i] = words[word][i];
            mask[i] = '*';
        }else if(grid[y][x+i] == words[word][i]){
            mask[i] = words[word][i];
            connect++;
        }else{
            isgood = false;
        }
    }

    for(int i = 0; i < num_words; i++){
        if(i != word && (int)(words[i].length()) == len){
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
        //debug();
        if (words_used == num_words) {
            if(score > best_score){
                best_score = score;
                make_snapshot();
            }
        }

        int best = 0;

        for (int i = 0; i < len; i++) {
            for (int j = 0; j < num_words; j++) {
                if (!used[j]) {
                    int len2 = (int)(words[j].length());
                    for (int k = 0; k < len2; k++) {
                        const char *w1 = words[word].c_str();
                        const char *w2 = words[j].c_str();

                        if (w1[i] == w2[k]) {
                            int s = solveH(x + i, y - k, j, score+connect);
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

int solveH(int x, int y, int word, int score){
    int len = (int)(words[word].length());
    char buf[len+1];
    char mask[len+1];
    int connect = 0;
    bool isgood = true;
    for(int i = 0; i < len; i++){
        buf[i] = grid[y+i][x];
        if(grid[y+i][x] == 0 && grid[y+i][x+1] == 0 && grid[y+i][x-1] == 0){
            grid[y+i][x] = words[word][i];
            mask[i] = '*';
        }else if(grid[y+i][x] == words[word][i]){
            mask[i] = words[word][i];
            connect++;
        }else{
            isgood = false;
        }
    }

    for(int i = 0; i < num_words; i++){
        if(i != word && (int)(words[i].length()) == len){
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
        used[word] = true;
        words_used++;
        //debug();
        if (words_used == num_words) {
            if(score > best_score){
                best_score = score;
                make_snapshot();
            }
        }


        for (int i = 0; i < len; i++) {
            for (int j = 0; j < num_words; j++) {
                if (!used[j]) {
                    int len2 = (int)(words[j].length());
                    for (int k = 0; k < len2; k++) {
                        const char *w1 = words[word].c_str();
                        const char *w2 = words[j].c_str();

                        if (w1[i] == w2[k]) {
                            solveW(x - k, y + i, j, score+connect);
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

/*
babel
javascript
react
docker
ember
meteor
backbone
express
vue
electron
nodejs
*/


int main(){
    string c;
    getline(cin, c);
    std::transform(c.begin(), c.end(), c.begin(), ::tolower);
    while(c.length()){
        words.push_back(c);
        getline(cin, c);
        std::transform(c.begin(), c.end(), c.begin(), ::tolower);
    }

    num_words = (int)words.size();
    used.assign(num_words, 0);

    solveW(grid_width/2, grid_height/2, 0, 0);
    solveH(grid_width/2, grid_height/2, 0, 0);

    instaExit();
}