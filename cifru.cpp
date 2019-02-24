/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("cifru.in", "r", stdin);
FILE *fout = freopen("cifru.out", "w", stdout);

const int MAX_N = 1 + 2000;
const int MOD = 19997;

int n, k;

int div[MAX_N], nrDiv;
int dp[MAX_N];

void readData() {
    scanf("%d%d", &n, &k);
}

void getDiv() {
    for(int i = 2; i <= n; ++i) {
        if(k % i == 0) {
            div[++nrDiv] = i;
        }
    }
}

void getDP() {
    dp[0] = dp[1] = 1;
    for(int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1];
        int A = 1, pos = i - 1;
        for(int j = 1; j <= nrDiv && div[j] <= i; ++j) {
            for(; pos > i - div[j]; --pos) {
                A = (A * pos) % MOD;
            }
            dp[i] = (dp[i] + A * dp[i - div[j]]) % MOD;
        }
    }
}

void writeData() {
    printf("%d", dp[n]);
}

int main() {
    readData();
    getDiv();
    getDP();
    writeData();
}
