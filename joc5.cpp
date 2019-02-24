/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("joc5.in", "r", stdin);
FILE *fout = freopen("joc5.out", "w", stdout);

const int MAX_N = 1 + 100;

int mat[MAX_N][MAX_N];

void solveTestCase(const int &N) {
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    int xorSum = 0;
    for(int i = 1; i <= N; i++) {
        xorSum ^= mat[i][i];
    }

    if(xorSum) {
        printf("1\n");
    } else {
        printf("2\n");
    }
}

int main() {
    for( ; ; ) {
        int N; scanf("%d", &N);
        if(N == 0) {
            return 0;
        } else {
            solveTestCase(N);
        }
    }
}
