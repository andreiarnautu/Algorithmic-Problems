/**
  *  Worg
  */
#include <cstdio>
#include <cstdlib>

FILE *fin = freopen("oras.in", "r", stdin); FILE *fout = freopen("oras.out", "w", stdout);

const int kMaxN = 200 + 5;

int sol[kMaxN][kMaxN];

void Expand(const int n) {
    sol[n + 1][n + 2] = 1;

    for(int i = 1; i <= n; i++) {
        sol[i][n + 1] = 1;
        sol[n + 2][i] = 1;
    }
}

void TypeOne(const int n) {
    sol[1][2] = sol[2][3] = sol[3][1] = 1;

    for(int i = 5; i <= n; i += 2) {
        Expand(i - 2);
    }
}

void TypeTwo(const int n) {
    if(n == 4) {
        printf("-1\n"); exit(0);
    }

    sol[1][2] = sol[1][6] = sol[2][3] = sol[2][4] = sol[3][1] = sol[3][6] = sol[4][1] = sol[4][3] = sol[4][5] = sol[5][1] = sol[5][2] = sol[5][3] = sol[6][2] = sol[6][4] = sol[6][5] = 1;

    for(int i = 8; i <= n; i += 2) {
        Expand(i - 2);
    }
}

void WriteMatrix(const int n) {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            printf("%d", sol[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int N; scanf("%d", &N);

    if(N % 2 == 1) {
        TypeOne(N);
    } else {
        TypeTwo(N);
    }

    WriteMatrix(N);
}
