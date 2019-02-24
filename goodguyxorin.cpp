/**
  *  Worg
  */
#include <cstdio>

using namespace std;

const int MAX_N = 2200;

int mat[MAX_N][MAX_N], sol[MAX_N][MAX_N];
int n, m, x;

void readData() {
    scanf("%d%d%d", &n, &m, &x);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            scanf("%d", &mat[i][j]);
}

void solveMatrix() {
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            int firstLin = (i - 1) * x + 1;
            int lastLin = i * x;
            int firstCol = (j - 1) * x + 1;
            int lastCol = j * x;
            for(int k1 = firstLin; k1 <= lastLin; ++k1)
                for(int k2 = firstCol; k2 <= lastCol; ++k2)
                    sol[k1][k2] = mat[i][j];
        }
    }

    for(int i = 1; i <= n * x; ++i) {
        for(int j = 1; j <= m * x; ++j) {
            printf("%d ", sol[i][j]);
        }
        printf("\n");
    }
}

int main() {
    readData();
    solveMatrix();
}
