/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

#define pb          push_back
#define inf         2000000000
#define MAX_N       50
#define MAX_W       1000
#define inFile      "lanterna.in"
#define outFile     "lanterna.out"

using namespace std;

struct trio {
    int a, t, w;
};

queue < int > Q;
vector < trio > G[1 + MAX_N];
vector < trio >::iterator it;

bool base[1 + MAX_N], inQueue[1 + MAX_N];
int dp[1 + MAX_N][1 + MAX_W], add[1 + MAX_N][1 + MAX_W];
int n, k, m;

trio makeTrio(int _a, int _t, int _w) {

    trio aux;
    aux.a = _a, aux.t = _t, aux.w = _w;
    return aux;
}

void elemset(int *p, int nr, int val) {

    for(int  i = 1; i <= nr; ++i)
        p[i] = val;
}

void readData() {

    freopen(inFile, "r", stdin);
    scanf("%d %d ", &n, &k);
    for(int i = 1; i <= n; ++i)
        scanf("%d ",&base[i]);

    int _a, _b, _t, _w;
    scanf("%d ", &m);
    for(int i = 1; i <= m; ++i) {

        scanf("%d %d %d %d ", &_a, &_b, &_t, &_w);
        G[_a].pb(makeTrio(_b, _t, _w));
        G[_b].pb(makeTrio(_a, _t, _w));
    }
}

void setDP() {

    for(int i = 1; i <= n; ++i)
        for(int j = 0; j <= MAX_W; ++j)
            dp[i][j] = inf;
}

void bellmanFord() {

    dp[1][0] = 0;
    Q.push(1); inQueue[1] = 1;

    int node, i, cost, W, ok = 0;
    while(!Q.empty()) {

        node = Q.front(); Q.pop();
        inQueue[node] = 0;

        if(base[node])
            for(i = 0; i <= k; ++i)
                add[node][i] = 0;

        for(it = G[node].begin(); it != G[node].end(); ++it) {

            ok = 0;
            for(i = 0; i <= k; ++i)
                if(dp[node][i] != inf) {

                    W = max(i, add[node][i] + it->w);
                    if(W > k)
                        continue;
                    if(dp[it->a][W] > dp[node][i] + it->t)
                        dp[it->a][W] = dp[node][i] + it->t, add[it->a][W] = add[node][i] + it->w, ok = 1;
                    else if(dp[it->a][W] == dp[node][i] + it->t && add[node][i] + it->w < add[it->a][W])
                        add[it->a][W] = add[node][i] + it->w, ok = 1;
                }
            if(ok && !inQueue[it->a])
                inQueue[it->a] = 1, Q.push(it->a);
        }

    }
}

void writeData() {

    freopen(outFile, "w", stdout);

    int tmin = inf, wmin;

    for(int j = k; j >= 0; --j)
        if(dp[n][j] <= tmin)
            tmin = dp[n][j], wmin = j;
    if(!wmin)
        ++wmin;

    printf("%d %d ", tmin, wmin);
}

int main() {

    readData();
    setDP();
    bellmanFord();
    writeData();
    return 0;
}
