/**
  *  Worg
  */
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
FILE *fin = freopen("hamilton.in", "r", stdin);
FILE *fout = freopen("hamilton.out", "w", stdout);

const int MAX_N = 18,
          MAX_INF = 0x3fffffff;

int cost[MAX_N][MAX_N], dp[1 << MAX_N][MAX_N];
int vecini[MAX_N];
int n, m;
char bit[1 << MAX_N];

void readData() {

    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i) {

        int u, v, c; scanf("%d%d%d", &u, &v, &c);
        cost[u][v] = c;
        vecini[v] ^= (1 << u);
    }
    for(int i = 0; i < n; ++i)
        bit[1 << i] = i;
}

void runDp() {

    int limit = 1 << (n - 1);
    for(int i = 0; i < limit; ++i)
        for(int j = 0; j < n; ++j)
            dp[i][j] = MAX_INF;
    dp[0][n - 1] = 0;

    for(int mask = 1; mask < limit; ++mask) {

        int tmpMask = mask;
        while(tmpMask) {

            int newMask = tmpMask & (tmpMask - 1);
            int v = bit[newMask ^ tmpMask]; /* calculam dp[mask][v] */
            tmpMask = newMask;

            int config = vecini[v];
            while(config) {

                int newConfig = config & (config - 1);
                int u = bit[config ^ newConfig];
                config = newConfig;

                dp[mask][v] = min(dp[mask][v], dp[mask ^ (1 << v)][u] + cost[u][v]);
            }
        }
    }

    int sol = MAX_INF;
    for(int i = 0; i < n - 1; ++i)
        if(cost[i][n - 1])
            sol = min(sol, dp[limit - 1][i] + cost[i][n - 1]);

    if(sol == MAX_INF)
        printf("Nu exista solutie");
    else
        printf("%d\n", sol);
}

int main() {

    readData();
    runDp();
    return 0;
}
