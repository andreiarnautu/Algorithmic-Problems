/**
  *  Worg
  *  Iterative DFS
  */
#include <cstdio>
#include <vector>

#define pb          push_back
#define MAX_N       1 + 100000
#define inFile      "dfs.in"
#define outFile     "dfs.out"

using namespace std;

vector < int > G[MAX_N];

bool viz[MAX_N];
int nxt[MAX_N], father[MAX_N];
int n, m, ccCount;

void readData() {

    freopen(inFile, "r", stdin);
    scanf("%d %d ", &n, &m);

    int x, y;
    for(int i = 1; i <= m; ++i) {

        scanf("%d %d ", &x, &y);
        G[x].pb(y); G[y].pb(x);
    }
}

void dfs(int node) {

    int aux;
    bool ok;
    do {

        viz[node] = 1;
        ok = 0;

        for(; nxt[node] < G[node].size(); ++nxt[node])
            if(!viz[G[node][nxt[node]]]) {

                ok = 1;
                aux = G[node][nxt[node]];
                father[aux] = node;
                ++nxt[node];
                node = aux;
                break;
            }

        if(!ok && father[node])
            node = father[node], ok = 1;

    }while(ok);
}

void writeData() {

    freopen(outFile, "w", stdout);
    printf("%d", ccCount);
}

int main() {

    readData();
    for(int i = 1; i <= n; ++i)
        if(!viz[i]) {

            ++ccCount;
            dfs(i);
        }
    writeData();
    return 0;
}
