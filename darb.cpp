/**
  *  Worg
  */
#include <cstdio>
#include <vector>

#define pb          push_back

using namespace std;
FILE *fin = freopen("darb.in", "r", stdin);
FILE *fout = freopen("darb.out", "w", stdout);

const int MAX_N = 1 + 100000;

vector < int > G[MAX_N];

bool viz[MAX_N];
int depth[MAX_N];
int n;

void readData() {

    scanf("%d ", &n);
    for(int i = 1; i <= n; ++i) {

        int a, b;
        scanf("%d %d ", &a, &b);
        G[a].pb(b);
        G[b].pb(a);
    }
}

void dfs(int node) {

    viz[node] = true;
    for(vector < int >::iterator it = G[node].begin(); it != G[node].end(); ++it)
        if(!viz[*it]) {

            depth[*it] = depth[node] + 1;
            dfs(*it);
        }
}

int getMax() {

    int ret = 1;
    for(int i = 2; i <= n; ++i)
        ret = (depth[i] > depth[ret]) ? i : ret;
    return ret;
}

int main() {

    readData();
    dfs(1);
    int node = getMax();
    for(int i = 1; i <= n; ++i)
        viz[i] = 0, depth[i] = 1;
    dfs(node);
    int sol = 0;
    for(int i = 1; i <= n; ++i)
        sol = (depth[i] > sol) ? depth[i] : sol;
    printf("%d", sol);
    return 0;
}
