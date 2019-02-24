/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("carry.in", "r", stdin);
FILE *fout = freopen("carry.out", "w", stdout);

const int MAX_N = 1 + 100000;
const int MAX_K = 1 + 100;
const int MOD = 30211;

char sir[MAX_N + 1];
int c[MAX_N + 1];
int N, K;

int dp[MAX_N][MAX_K][2];

void readData() {
    scanf("%d%d", &N, &K);
    scanf("%s", sir + 1);

    for(int i = 1; i <= N; ++i) {
        c[i] = sir[i] - '0';
    }
}

void runDP() {
    if(N == 1) {
        if(K == 0) {
            printf("%d", 9 - c[N]);
        }
        else {
            printf("%d", c[N]);
        }
        return;
    }
    else {
        dp[1][0][0] = 10 - c[N];
        dp[1][1][1] = c[N];
    }

    for(int i = 2; i < N; ++i) {
        int x = c[N - i + 1];

        int limit = min(i, K);
        for(int j = 0; j <= limit; j++) {
            dp[i][j][0] = (dp[i - 1][j][0] * (10 - x) +
                           dp[i - 1][j][1] * (9 - x)) % MOD;
            if(j > 0) {
                dp[i][j][1] = (dp[i - 1][j - 1][0] * x + dp[i - 1][j - 1][1] * (x + 1)) % MOD;
            }
        }
    }

    int limit = min(N, K);
    int x = c[1];
    for(int j = 0; j <= limit; ++j) {
        dp[N][j][0] = (dp[N - 1][j][0] * (9 - x) +
                       dp[N - 1][j][1] * max(0, 8 - x)) % MOD;
        if(j > 0) {
            dp[N][j][1] = (dp[N - 1][j - 1][0] * x +
                           dp[N - 1][j - 1][1] * min(9, x + 1)) % MOD;
        }
    }

    printf("%d", (dp[N][K][0] + dp[N][K][1]) % MOD);
}

int main() {
    readData();
    runDP();
    return 0;
}
