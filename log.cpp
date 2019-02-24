/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("log.in", "r", stdin);
FILE *fout = freopen("log.out", "w", stdout);

const int MAX_N = 1 + 10000;
const int MAX_INF = 0x3fffffff;

/*----------------------*/
int N, T1, T2, T3;
int a[MAX_N], b[MAX_N], dp[MAX_N];
/*----------------------*/

void readInput() {
    scanf("%d%d%d%d", &N, &T1, &T2, &T3);
    for(int i = 1; i <= N; i++) {
        scanf("%d%d", &a[i], &b[i]);
    }
}

void runDP() {
    dp[1] = T3 * (a[1] - b[1]) * (a[1] - b[1]);

    for(int i = 2; i <= N; i++) {
        dp[i] = dp[i - 1] + T3 * (a[i] - b[i]) * (a[i] - b[i]) + T1; /* we initialize dp[i] */
        for(int j = i - 1; j > 0; j--) {
            if(b[j] != a[j + 1]) {
                break;
            } else {
                dp[i] = min(dp[i], dp[j - 1] + T2 * (i - j) + T3 * (a[j] - b[i]) * (a[j] - b[i]) + T1);
                if(j == 1) {
                    dp[i] = min(dp[i], dp[j - 1] + T2 * (i - j) + T3 * (a[j] - b[i]) * (a[j] - b[i])); /* -T1 */
                }
            }
        }
    }
}

void writeOutput() {
    printf("%d", dp[N]);
}

int main() {
    readInput();
    runDP();
    writeOutput();
    return 0;
}
