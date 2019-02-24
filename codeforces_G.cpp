/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
//FILE *fin = freopen("main.in", "r", stdin);
//FILE *fout = freopen("main.out", "w", stdout);

const int kMaxN = 1 + 50;

char A[kMaxN][kMaxN], B[kMaxN][kMaxN];
int N, M;
int type;

void ReadInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; i++) {
        scanf("%s", A[i] + 1);
    }
    for(int i = 1; i <= N; i++) {
        scanf("%s", B[i] + 1);
    }
    if(N % 2 == 0) {
        type = 0;
    } else {
        type = 1;
    }
}

bool Perfect(char mat[kMaxN][kMaxN]) {
    if(type == 0) {
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= M; j++) {
                if(i % 2 == 1 && mat[i][j] != 'U') {
                    return false;
                }
                if(i % 2 == 0 && mat[i][j] != 'D') {
                    return false;
                }
            }
        }
        return true;
    } else {
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= M; j++) {
                if(j % 2 == 1 && mat[i][j] != 'L') {
                    return false;
                }
                if(j % 2 == 0 && mat[i][j] != 'R') {
                    return false;
                }
            }
        }
        return true;
    }
}

vector<pair<int, int > > Normalize(char mat[kMaxN][kMaxN]) {
    vector<pair<int, int > > moves;

    bool now = 0;
    while(!Perfect(mat)) {
        if(now == 0) {
            for(int i = 1; i < N; i++) {
                for(int j = 1; j < M; j++) {
                    if(mat[i][j] == 'U' && mat[i][j + 1] == 'U' && mat[i + 1][j] == 'D' && mat[i + 1][j + 1] == 'D') {
                        mat[i][j] = mat[i + 1][j] = 'L';
                        mat[i][j + 1] = mat[i + 1][j + 1] = 'R';
                        moves.push_back(make_pair(i, j));
                    }
                }
            }
        } else {
            for(int i = 1; i < N; i++) {
                for(int j = 1; j < M; j++) {
                    if(mat[i][j] == 'L' && mat[i + 1][j] == 'L' && mat[i][j + 1] == 'R' && mat[i + 1][j + 1] == 'R') {
                        mat[i][j] = mat[i][j + 1] = 'U';
                        mat[i + 1][j] = mat[i + 1][j + 1] = 'D';
                        moves.push_back(make_pair(i, j));
                    }
                }
            }
        }

        now ^= 1;
    }

    return moves;
}

int main() {
    ReadInput();
    vector<pair<int, int > > first = Normalize(A);
    vector<pair<int, int > > second = Normalize(B);
    reverse(second.begin(), second.end());
    printf("%d\n", (int)first.size() + (int)second.size());
    for(auto p : first) {
        printf("%d %d\n", p.first, p.second);
    }
    for(auto p : second) {
        printf("%d %d\n", p.first, p.second);
    }

    return 0;
}
