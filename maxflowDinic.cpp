/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("maxflow.in", "r", stdin);
FILE *fout = freopen("maxflow.out", "w", stdout);

const int MAX_N = 1000, MAX_INF = 0x3fffffff;

vector < int > G[1 + MAX_N];
int cap[1 + MAX_N][1 + MAX_N];

queue < int > q;
vector < int > GL[1 + MAX_N];
int depth[1 + MAX_N], path[1 + MAX_N];
bool checked[1 + MAX_N];

int n, m;

void readData() {

    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i) {

        int u, v, c; scanf("%d%d%d", &u, &v, &c);
        G[u].push_back(v); G[v].push_back(u);
        cap[u][v] = c;
    }
}

bool buildGL() {

    for(int i = 1; i <= n; ++i)
        checked[i] = false;

    int node = 1;
    q.push(node);
    depth[node] = 0;
    checked[node] = true;

    while(!q.empty()) {

        node = q.front(); q.pop();
        for(int nxt : G[node])
            if(!checked[nxt] && cap[node][nxt] > 0) {

                depth[nxt] = depth[node] + 1;
                q.push(nxt);
                checked[nxt] = true;
            }
    }
    for(int i = 1; i <= n; ++i)
        GL[i].clear();
    for(node = 1; node <= n; ++node)
        for(int nxt : G[node])
            if(depth[node] - depth[nxt] == -1 && cap[node][nxt] > 0)
                GL[node].push_back(nxt);
    return checked[n];
}

int DFS(int node) {

    checked[node] = true;
    path[depth[node]] = node;

    if(node == n)
        return MAX_INF;
    else {

        for(int nxt : GL[node])
            if(!checked[nxt] && cap[node][nxt] > 0) {

                int x = DFS(nxt);
                if(x > 0)
                    return min(cap[node][nxt], x);
            }
        return 0;
    }
}

int pushFlow() {

    for(int i = 1; i <= n; ++i)
        checked[i] = false;
    int currentFlow = 0, flow = DFS(1);
    while(flow > 0) {

        for(int i = 0; i < depth[n]; ++i) {

            cap[path[i]][path[i + 1]] -= flow;
            cap[path[i + 1]][path[i]] += flow;
        }
        currentFlow += flow;
        for(int i = 1; i <= n; ++i)
            checked[i] = false;
        flow = DFS(1);
    }
    return currentFlow;
}

int main() {

    readData();

    int totalFlow = 0;
    while(buildGL())
        totalFlow += pushFlow();
    printf("%d", totalFlow);
    return 0;
}
