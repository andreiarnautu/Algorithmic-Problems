/**
  *  Worg
  *  Dinic's Algorithm
  */
#include <queue>
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("cmcm.in", "r", stdin);
FILE *fout = freopen("cmcm.out", "w", stdout);

const int MAX_N = 300, DIM = 2 * (1 + MAX_N), MAX_INF = 0x3fffffff;

vector < int > G[DIM]; /* general */
vector < pair<int,int> > edges;
int cap[DIM][DIM], cost[DIM][DIM];
int n, m, e, S, D;

queue < int > q;
int dmin[DIM], father[DIM];
bool inQueue[DIM];

int cnt, totalCost;

void readData() {

    scanf("%d%d%d", &n, &m, &e);
    S = 0; D = n + m + 1;
    for(int i = 1; i <= n; ++i) {

        G[S].push_back(i); G[i].push_back(S);
        cap[S][i] = 1;
    }
    for(int i = n + 1; i <= n + m; ++i) {

        G[i].push_back(D); G[D].push_back(i);
        cap[i][D] = 1;
    }
    for(int i = 1; i <= e; ++i) {

        int u, v, c; scanf("%d%d%d", &u, &v, &c);
        v += n;
        G[u].push_back(v); G[v].push_back(u);
        cap[u][v] = 1;
        cost[u][v] = c; cost[v][u] = -c;
        edges.push_back(make_pair(u, v));
    }
}

bool bellmanFord() {

    for(int i = S; i <= D; ++i) {

        inQueue[i] = false;
        dmin[i] = MAX_INF;
    }
    int node = S;
    q.push(node); dmin[node] = 0;
    while(!q.empty()) {

        node = q.front(); q.pop(); inQueue[node] = false;
        for(int nxt : G[node])
            if(dmin[node] + cost[node][nxt] < dmin[nxt] && cap[node][nxt] > 0) {

                father[nxt] = node;
                dmin[nxt] = dmin[node] + cost[node][nxt];
                if(!inQueue[nxt]) {

                    inQueue[nxt] = true; q.push(nxt);
                }
            }
    }

    if(dmin[D] == MAX_INF) {

        return false;
    }

    else {

        cnt++;
        node = D;
        while(node != S) {

            cap[father[node]][node]--;
            cap[node][father[node]]++;
            totalCost += cost[father[node]][node];
            node = father[node];
        }
        return true;
    }
}

int main() {

    readData();
    while(bellmanFord());
    printf("%d %d\n", cnt, totalCost);
    for(int i = 0; i < (int)edges.size(); ++i)
        if(!cap[edges[i].first][edges[i].second])
            printf("%d ", i + 1);
    return 0;
}
