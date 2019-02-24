/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;
FILE *fin = freopen("ca.in", "r", stdin);
ofstream fout("ca.out");

const int MAX_N = 6;
const int MAX_M = 6;
const int MAX_SIZE = 300000;
const int dx[] = {-1, -1, -1,  0, 0,  1, 1, 1};
const int dy[] = {-1,  1,  0, -1, 1, -1, 0, 1};
const int dSize = 8;

/*------------------------*/
int N, M, C;
char init[MAX_N][MAX_M];
/*------------------------*/
char now[MAX_N][MAX_M];
char word[MAX_SIZE], lgWord;

long long appCount;

vector< pair< string,long long > > SOL;
/*------------------------*/

void readData() {
    scanf("%d%d%d ", &N, &M, &C);
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= M; ++j) {
            scanf("%c ", &init[i][j]);
        }
    }
}

void initNow() {
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= M; ++j) {
            now[i][j] = init[i][j];
        }
    }
}

bool inTheMatrix(int x, int y) {
    /* Neo was here */
    return (1 <= x && x <= N && 1 <= y && y <= M);
}

void Run(int x, int y, int pos) {
    /* word[pos] is located at now[x][y] */


    if(now[x][y] == '?') { /* if here was a question mark before choosing this character */
        now[x][y] = word[pos];
        if(pos == lgWord - 1) { /* if we settled the word's final character, we stop and increase the appearances */
            appCount++;
        } else { /* otherwise, we stop */
            for(int i = 0; i < dSize; i++) {
                int newX = x + dx[i];
                int newY = y + dy[i];
                if(inTheMatrix(newX, newY) && (now[newX][newY] == word[pos + 1] || now[newX][newY] == '?')) {
                    Run(newX, newY, pos + 1);
                }
            }
        }

        now[x][y] = '?'; /* we set the character to be the question mark again */

    } else { /* if there was no question mark, the approach is similar */
        if(pos == lgWord - 1) {
            appCount++;
        } else {
            for(int i = 0; i < dSize; i++) {
                int newX = x + dx[i];
                int newY = y + dy[i];
                if(inTheMatrix(newX, newY) && (now[newX][newY] == word[pos + 1] || now[newX][newY] == '?')) {
                    Run(newX, newY, pos + 1);
                }
            }
        }
    }
}

void solveWord() {
    initNow();
    scanf("%s", word); lgWord = strlen(word); appCount = 0;

    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= M; ++j) {
            /* we need to find a starting position */
            if(init[i][j] == word[0] || init[i][j] == '?') {
                Run(i, j, 0);
            }
        }
    }

    if(appCount != 0) { /* if we were able to form the word */
        string current; current.clear();
        for(int i = 0; i < lgWord; i++) {
            current += word[i];
        }
        SOL.push_back(make_pair(current, appCount));
    }
}

void writeData() {
    fout << (int)SOL.size() << '\n';
    for(vector< pair< string,long long > >::iterator it = SOL.begin(); it != SOL.end(); ++it) {
        fout << it->first << " " << it->second << '\n';
    }

    for(int i = 1; i <= (int)SOL.size(); ++i) {
        char c = 'a' + (SOL[i - 1].second % 26);
        fout << c;
    }

    fout << '\n';
}

int main() {
    readData();
    for(int i = 1; i <= C; ++i) {
        solveWord();
    }
    writeData();
}
