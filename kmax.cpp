/**
  *  Worg
  */
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
FILE *fin = freopen("kmax.in", "r", stdin);
FILE *fout = freopen("kmax.out", "w", stdout);

const int MAX_N = 1 + 300;

int N, K, R;
int dp[3][MAX_N][MAX_N], sdp[3][MAX_N][MAX_N];

void readInput() {
    scanf("%d%d%d", &N, &K, &R);
}

void runDP() {
    dp[1][1][1] = sdp[1][1][1] = 1;

    for(int n = 2; n <= N; n++) {
        /* calculam dp[n][1][u] */
        for(int u = 1; u <= n - 1; u++) {
            for(int x = 1; x <= min(n - 1, K); x++) {
                dp[2][1][u] = (dp[2][1][u] + sdp[1][x][n - 1] - sdp[1][x][u - 1] + R) % R;
            }
        }

        for(int x = 2; x <= min(n, K); x++) {
            for(int u = 1; u <= n; u++) {
                dp[2][x][u] = sdp[1][x - 1][u - 1];
            }
        }

        for(int x = 1; x <= min(n, K); x++) {
            for(int u = 1; u <= n; u++) {
                sdp[2][x][u] = (sdp[2][x][u - 1] + dp[2][x][u]) % R;
            }
        }

        for(int x = 1; x <= min(n, K); x++) {
            for(int u = 1; u <= n; u++) {
                dp[1][x][u] = dp[2][x][u];
                sdp[1][x][u] = sdp[2][x][u];
            }
        }

        for(int x = 1; x <= min(K, N); x++) {
            for(int u = 1; u <= N; u++) {
                sdp[2][x][u] = dp[2][x][u] = 0;
            }
        }
    }
}

void writeOutput() {
    int Answer = 0;
    for(int i = 1; i <= min(K, N); i++) {
        Answer = (Answer + sdp[1][i][N]) % R;
    }
    printf("%d", Answer);
}

int main() {
    readInput();
    runDP();
    writeOutput();

    return 0;
}
