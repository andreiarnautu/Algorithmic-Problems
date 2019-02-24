/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

#define pb          push_back

using namespace std;
FILE *fin = freopen("atac.in", "r", stdin);
FILE *fout = freopen("atac.out", "w", stdout);

const int MAX_N = 1 + 32000,
          MAX_LOG = 1 + 20,
          INF = 1000000000;

struct neighbour {

    int vertex, cost;

    neighbour(const int &vertex, const int &cost) {

        this->vertex = vertex, this->cost = cost;
    }
};

vector < neighbour > G[MAX_N];

int rmq[MAX_LOG][MAX_N << 1], dp[MAX_N][MAX_LOG], ancestor[MAX_N][MAX_LOG];
int pos[MAX_N], list[MAX_N << 1], depth[MAX_N << 1], father[MAX_N << 1], lg[MAX_N << 1];
int k;
int n, m, p, A, B, C, D, x, y;

void readData() {

    scanf("%d %d %d ", &n, &m, &p);
    for(int i = 2; i <= n; ++i) {

        int vertex, cost;
        scanf("%d %d ", &vertex, &cost);

        G[i].pb(neighbour(vertex, cost));
        G[vertex].pb(neighbour(i, cost));
    }
    scanf("%d %d %d %d %d %d", &x, &y, &A, &B, &C, &D);
}


void eulerianDfs(int node, int level) {

    list[++k] = node;
    depth[k] = level;
    pos[node] = k;

    for(vector < neighbour >::iterator it = G[node].begin(); it != G[node].end(); ++it)
        if(it->vertex != father[node]) {

            father[it->vertex] = node;
            eulerianDfs(it->vertex, level + 1);
            list[++k] = node;
            depth[k] = level;
        }
}

void getRMQ() {

    for(int i = 2; i <= k; ++i)
        lg[i] = lg[i >> 1] + 1;
    for(int i = 1; i <= k; ++i)
        rmq[0][i] = i;

    for(int i = 1; (1 << i) < k; ++i) {

        int lastPos = k - (1 << i);
        for(int j = 1; j <= lastPos; ++j)
            rmq[i][j] = (depth[rmq[i - 1][j]] < depth[rmq[i - 1][j + (1 << (i - 1))]]) ? rmq[i - 1][j] : rmq[i - 1][j + (1 << (i - 1))];
    }
}

int LCA(int x, int y) {

    int a = pos[x], b = pos[y];
    if(a > b)
        swap(a, b);

    int level = lg[b - a + 1];
    return (depth[rmq[level][a]] < depth[rmq[level][b - (1 << level) + 1]]) ? list[rmq[level][a]] : list[rmq[level][b - (1 << level) + 1]];
}

void dfs(int node, int level, int cost) {

    dp[node][0] = cost, ancestor[node][0] = father[node];

    for(int i = 1; (1 << i) <= level; ++i) {

        dp[node][i] = min(dp[node][i - 1], dp[ancestor[node][i - 1]][i - 1]);
        ancestor[node][i] = ancestor[ancestor[node][i - 1]][i - 1];
    }

    for(vector < neighbour >::iterator it = G[node].begin(); it != G[node].end(); ++it)
        if(it->vertex != father[node])
            dfs(it->vertex, level + 1, it->cost);
}

int getMinEdge(int x, int y) {

    if(depth[pos[x]] <= depth[pos[y]])
        return INF;
    int logaritm = lg[depth[pos[x]] - depth[pos[y]]];
    return min(dp[x][logaritm], getMinEdge(ancestor[x][logaritm], y));
}

int main() {

    readData();
    eulerianDfs(1, 0);
    getRMQ();
    for(int i = 0; i < MAX_LOG; ++i)
        dp[1][i] = INF;
    dfs(1, 0, 0);

    for(int i = 1; i <= m; ++i) {

        int node = LCA(x, y);
        int z;
        if(x == y)
            z = 0;
        else
            z = min(getMinEdge(x, node), getMinEdge(y, node));
        if(m - i + 1 <= p)
            printf("%d\n", z);

        x = (x * A + y * B) % n + 1;
        y = (y * C + z * D) % n + 1;
    }
    return 0;
}
