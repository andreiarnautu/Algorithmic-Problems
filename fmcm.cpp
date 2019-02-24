/**
  *  Worg
  *  Minimum Cost Max Flow
  */
#include <queue>
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("fmcm.in", "r", stdin);
FILE *fout = freopen("fmcm.out", "w", stdout);

const int MAX_N = 350, MAX_INF = 0x3fffffff;

vector <int> G[1 + MAX_N]; /* general */
int cap[1 + MAX_N][1 + MAX_N], cost[1 + MAX_N][1 + MAX_N];
int n, m, S, D;

queue < int > q; /* Bellman Ford */
int inQueue[1 + MAX_N], dmin[1 + MAX_N], maxFlow[1 + MAX_N], father[1 + MAX_N];

int totalCost = 0;

void readData() {

    scanf("%d%d%d%d", &n, &m, &S, &D);
    for(int i = 1; i <= m; ++i) {

        int x, y, c, z; scanf("%d%d%d%d", &x, &y, &c, &z);
        G[x].push_back(y); G[y].push_back(x);
        cap[x][y] = c; cost[x][y] = z; cost[y][x] = -z;
    }
}

bool bellmanFord() {

    for(int i = 1; i <= n; ++i) {

        inQueue[i] = false;
        dmin[i] = MAX_INF;
        father[i] = 0;
    }
    int node = S;
    q.push(node); inQueue[node] = true; dmin[node] = 0; maxFlow[node] = MAX_INF;
    while(!q.empty()) {

        node = q.front(); q.pop(); inQueue[node] = false;
        for(int nxt : G[node])
            if(dmin[node] + cost[node][nxt] < dmin[nxt] && cap[node][nxt] > 0) {

                father[nxt] = node;
                dmin[nxt] = dmin[node] + cost[node][nxt];
                maxFlow[nxt] = min(cap[node][nxt], maxFlow[node]);
                if(!inQueue[nxt]) {

                    q.push(nxt); inQueue[nxt] = true;
                }
            }
    }

    if(dmin[D] == MAX_INF) {

        return false;
    }
    else {

        node = D;
        while(node != S) {

            cap[father[node]][node] -= maxFlow[D];
            cap[node][father[node]] += maxFlow[D];
            totalCost += maxFlow[D] * cost[father[node]][node];
            node = father[node];
        }
        return true;
    }
}

int main() {

    readData();
    while(bellmanFord());
    printf("%d", totalCost);
    return 0;
}
