/**
  *  Worg
  */
#include <map>
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("desc2.in", "r", stdin);
FILE *fout = freopen("desc2.out", "w", stdout);

const int MOD = 10007;
const int MAX_N = 1 + 10000;

int dp[MAX_N];
int N, K, X;

void runDP() {
    dp[0] = 1;

    for(int i = 1; i <= K; i++) {
        for(int j = i; j <= N; j++) {
            dp[j] = (dp[j] + dp[j - i]) % MOD;
        }
    }

    printf("%d", dp[N]);
}

int main() {
    scanf("%d%d%d", &N, &K, &X);
    N -= X * (K) * (K - 1) / 2 + K;

    if(N < 0) {
        printf("0\n"); return 0;
    } else {
        runDP();
    }
    return 0;
}
