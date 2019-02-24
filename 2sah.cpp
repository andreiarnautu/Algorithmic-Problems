/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("2sah.in", "r", stdin);
FILE *fout = freopen("2sah.out", "w", stdout);

const int MOD = 100003;

int t, N, K;

void readData() {
    scanf("%d%d%d", &t, &N, &K);
}

void taskOne() {
    long long answer = 1, aux = 3;
    for(int i = 1; i < K; i <<= 1) {
        if(i & (K - 1)) {
            answer = (answer * aux) % MOD;
        }
        aux = (aux * aux) % MOD;
    }
    printf("%lld", answer);
}

long long aux[3][3], sol[3][3], m[3][3];

void matrixProduct(long long a[][3], long long b[][3], long long c[][3]) {
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            c[i][j] = 0;
        }
    }

    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            for(int k = 0; k < 3; ++k) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }

    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            a[i][j] = c[i][j];
        }
    }
}

void taskTwo() {
    K = N + 2 - K;
    for(int i = 0; i < 3; ++i) {
        sol[i][i] = 1;
        aux[2][i] = 1;
    }
    aux[0][1] = aux[1][2] = 1;

    for(int i = 1; i <= (K - 1); i <<= 1) {
        if(i & (K - 1)) {
            matrixProduct(sol, aux, m);
        }
        matrixProduct(aux, aux, m);
    }

    printf("%d", sol[2][2]);
}

int main() {
    readData();
    if(t == 1) {
        taskOne();
    }
    else {
        taskTwo();
    }
}
