/**
  *  Worg
  */
#include <set>
#include <queue>
#include <cstdio>

using namespace std;
FILE *fin = freopen("arbciclu.in", "r", stdin);
FILE *fout = freopen("arbciclu.out", "w", stdout);

const int MAX_N = 1 + 100000;

set <int> G[MAX_N];
int n, m;
int degree[MAX_N];

queue <int> q;

void readData() {

    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        G[u].insert(v);
        G[v].insert(u);
        degree[u]++;
        degree[v]++;
    }
}

void solveGraph() {

    for(int i = 1; i <= n; ++i)
        if(degree[i] == 2) {
            q.push(i);
        }

    int solved = 0;

    while(!q.empty()) {
        int node = q.front(); q.pop();
        if(degree[node] != 2) {
            continue;
        }
        else {
            solved++;
            degree[node] = 0;

            int node1, node2;
            set <int>::iterator it = G[node].begin();
            node1 = *it;
            it++;
            node2 = *it;

            G[node].clear();
            G[node1].erase(node);
            G[node2].erase(node);
            degree[node1]--;
            degree[node2]--;

            if(G[node1].find(node2) == G[node1].end()) {
                G[node1].insert(node2);
                G[node2].insert(node1);
                degree[node1]++;
                degree[node2]++;
            }

            if(degree[node1] == 2) {
                q.push(node1);
            }
            if(degree[node2] == 2) {
                q.push(node2);
            }
        }
    }

    if(solved == n - 2 && n > 2) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }

    for(int i = 1; i <= n; ++i) {
        G[i].clear();
        degree[i] = 0;
    }
}

int main() {

    int t;
    for(scanf("%d", &t); t > 0; --t) {
        readData();
        solveGraph();
    }
    return 0;
}
