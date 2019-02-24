/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("acces.in", "r", stdin);
FILE *fout = freopen("acces.out", "w", stdout);

const int MAX_N = 1 + 1000;
const int bufferDim = 100000;

class inputReader {

private:
        char buffer[bufferDim];
        int pos = 0;

        bool digit(char c) {
            return('0' <= c && c <= '9');
        }

public:
        void getBuffer() {
            fread(buffer, 1, bufferDim, stdin);
            pos = 0;
        }

        void getInt(int &nr) {
            nr = 0;
            while(!digit(buffer[pos]))
                if(++pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == bufferDim)
                    getBuffer();
            }
        }
} cin;
/*--------------------------*/
int mat[MAX_N][MAX_N];
int N, M;
/*--------------------------*/
int SOL[MAX_N][MAX_N];

void readData() {
    cin.getBuffer();
    cin.getInt(N); cin.getInt(M);
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= M; ++j) {
            cin.getInt(mat[i][j]);
        }
    }
}

void preProcess() {
    for(int j = 1; j <= M; ++j) {
        if(mat[1][j] == 0) {
            SOL[1][j] = SOL[1][j - 1] + 1;
        } else {
            SOL[1][j] = 0;
        }
    }

    for(int i = 1; i <= N; ++i) {
        if(mat[i][1] == 0) {
            SOL[i][1] = SOL[i - 1][1] + 1;
        } else {
            SOL[i][1] = 0;
        }
    }

    for(int i = 2; i <= N; ++i) {
        for(int j = 2; j <= M; ++j) {
            if(mat[i][j] == 1) {
                if(!SOL[i - 1][j] || !SOL[i][j - 1]) {
                    SOL[i][j] = 0;
                } else if(SOL[i - 1][j] > 0 && SOL[i][j - 1] > 0) {
                    SOL[i][j] = -SOL[i - 1][j - 1];
                } else {
                    SOL[i][j] = min(SOL[i - 1][j], SOL[i][j - 1]);
                }
            } else {
                if(SOL[i - 1][j] > 0 && SOL[i][j - 1] > 0) {
                    SOL[i][j] = 1 + SOL[i - 1][j] + SOL[i][j - 1];
                    if(SOL[i - 1][j - 1] > 0) {
                        SOL[i][j] -= SOL[i - 1][j - 1];
                    } else {
                        SOL[i][j] += SOL[i - 1][j - 1];
                    }
                } else {
                    if(SOL[i - 1][j] > 0) {
                        SOL[i][j] = SOL[i - 1][j] + 1;
                    } else if(SOL[i][j - 1] > 0){
                        SOL[i][j] = SOL[i][j - 1] + 1;
                    } else {
                        SOL[i][j] = 1;
                    }
                }
            }
        }
    }
}

void solveQueries() {
    int Q;
    for(cin.getInt(Q); Q; --Q) {
        int x, y; cin.getInt(x); cin.getInt(y);
        printf("%d\n", SOL[x][y]);
    }
}

int main() {
    readData();
    preProcess();
    solveQueries();
    return 0;
}
