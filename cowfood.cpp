/**
  * Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("cowfood.in", "r", stdin);
FILE *fout = freopen("cowfood.out", "w", stdout);

const int MAX_K = 1 + 30;
const int MAX_S = 1 + 10000;
const int MAX_N = 1 + 20;
const int MOD = 3210121;

/*---------------------*/ /** General */
int K, S, N;
int a[MAX_N][MAX_K];
/*---------------------*/ /** DP & Back */
int dp[MAX_K][MAX_S];

int aux[MAX_N][MAX_K];
int maxA[MAX_K];
/*---------------------*/
int validConfigs;

void readData() {
    scanf("%d%d%d", &K, &S, &N);
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= K; j++) {
            scanf("%d", &a[i][j]);
        }
    }
}

void generateDP() {
    for(int i = 0; i <= S; i++) {
        dp[0][i] = 1;
    }
    for(int i = 1; i <= K; i++) {
        dp[i][0] = 1;
        for(int j = 1; j <= S; j++) {
            dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD;
        }
    }
}

void countValidExperiments(int level, int countExp) {
    if(level == N + 1) { /* we reached a final configuration, now we need to add it to the solution */
        int crtSum = 0;
        for(int i = 1; i <= K; i++) {
            crtSum += maxA[i];
        }

        if(crtSum <= S) {
            if(countExp % 2 == 0) {
                validConfigs = (validConfigs + dp[K][S - crtSum]) % MOD;
            } else {
                validConfigs = (validConfigs - dp[K][S - crtSum] + MOD) % MOD;
            }
        }
    } else {
        countValidExperiments(level + 1, countExp); /* we don't add the current experiment to the configuration */

        for(int i = 1; i <= K; i++) {
            aux[level][i] = maxA[i];
            maxA[i] = max(maxA[i], a[level][i]);
        }

        countValidExperiments(level + 1, countExp + 1); /* we add the current experiment to the configuration */

        for(int i = 1; i <= K; i++) { /* we return to the previous state */
            maxA[i] = aux[level][i];
        }
    }
}

void writeData() {

    /* there are 1 + S*K cases where there are not at least 2 non-zero quantities */

    validConfigs -= (1 + S * K); validConfigs += MOD; validConfigs %= MOD;

    printf("%d", validConfigs);
}

int main() {
    readData();
    generateDP();
    countValidExperiments(1, 0);
    writeData();
    return 0;
}
