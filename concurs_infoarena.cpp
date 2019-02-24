/**
  *  Worg
  */
#include <cstdio>
#include <vector>

#define pb          push_back

using namespace std;
FILE *fin = freopen("concurs.in", "r", stdin);
FILE *fout = freopen("concurs.out", "w", stdout);

const int MAX_N = 1 + 32000,
          MAX_LOG = 18;

vector < int > G[MAX_N];

bool hasFather[MAX_N];
int rmq[MAX_LOG][MAX_N << 1];
int points[MAX_N], list[MAX_N << 1], depth[MAX_N << 1], pos[MAX_N << 1], lg[MAX_N << 1];
int n, q, k;
int sol = -1, no1, no2;

void readData() {

    scanf("%d %d ", &n, &q);
    for(int i = 1; i <= n; ++i)
        scanf("%d ", &points[i]);
    for(int i = 1; i < n; ++i) {

        int x, y;
        scanf("%d %d ", &x, &y);
        G[x].pb(y);
        hasFather[y] = 1;
    }
}

void eulerianDfs(int node, int level) {

    list[++k] = node;
    depth[k] = level;
    pos[node] = k;

    for(vector < int >::iterator it = G[node].begin(); it != G[node].end(); ++it) {

        eulerianDfs(*it, level + 1);
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

        int lastPos = k - (1 << i) + 1;
        for(int j = 1; j <= lastPos; ++j)
            rmq[i][j] = (depth[rmq[i - 1][j]] < depth[rmq[i - 1][j + (1 << (i - 1))]]) ? rmq[i - 1][j] : rmq[i - 1][j + (1 << (i - 1))];
    }

}

int LCA(int firstNode, int secondNode) {

    int a = pos[firstNode], b = pos[secondNode];
    if(a > b)
        swap(a, b);

    int level = lg[b - a + 1];
    return (depth[rmq[level][a]] < depth[rmq[level][b - (1 << level) + 1]]) ? list[rmq[level][a]] : list[rmq[level][b - (1 << level) + 1]];
}

void solveQuery() {

    int x, y, commonAncestor;
    scanf("%d %d ", &x, &y);

    commonAncestor = LCA(x, y);
    if(points[commonAncestor] > sol || (points[commonAncestor] == sol && no1 > x) || (points[commonAncestor] == sol && no1 == x && no2 > y)) {

        sol = points[commonAncestor];
        no1 = x;
        no2 = y;
    }
}

int main() {

    readData();
    for(int i = 1; i <= n; ++i)
        if(!hasFather[i]) {

            eulerianDfs(i, 0);
            break;
        }
    getRMQ();
    for(int i = 1; i <= q; ++i)
        solveQuery();
    printf("%d %d %d", sol, no1, no2);
    return 0;
}
