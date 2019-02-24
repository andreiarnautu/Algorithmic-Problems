/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("cast.in", "r", stdin);
FILE *fout = freopen("cast.out", "w", stdout);

const int kMaxN = 12;
const int kMaxInf = 2000000000;

/*-------- Input data --------*/
int test_count;
int N;
int cost[kMaxN][kMaxN];
/*-------- Algo data --------*/
int dp[1 << kMaxN][kMaxN];
/*-------- --------*/

void ReadTestData() {
    scanf("%d", &N);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            scanf("%d", &cost[i][j]);
        }
    }
}

void RunDp() {
    const int kMaxMask = (1 << N) - 1;
    for(int mask = 1; mask <= kMaxMask; mask ++) {
        for(int i = 0; i < N; i++) {
            if(mask & (1 << i)) {
                if(mask == (1 << i)) {
                    dp[mask][i] = 0; continue;
                }
                dp[mask][i] = kMaxInf;
                int other = mask ^ (1 << i);
                for(int config = other; config > 0; config = (config - 1) & other) {
                    for(int j = 0; j < N; j++) {
                        if(config & (1 << j)) {
                            dp[mask][i] = std::min(dp[mask][i], cost[i][j] + std::max(dp[config][j], dp[mask ^ config][i]));
                        }
                    }
                }
            }
        }
    }
}

int main() {
    for(scanf("%d", &test_count); test_count > 0; test_count--) {
        ReadTestData();
        RunDp();
        printf("%d\n", dp[(1 << N) - 1][0]);
    }
    return 0;
}
