/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("harta.in", "r", stdin);
FILE *fout = freopen("harta.out", "w", stdout);

const int MAX_N = 100, DIM = 2 * (MAX_N + 2), MAX_INF = 0x3fffffff;

vector < int > G[DIM];
int cap[DIM][DIM];

queue < int > q;
vector < int > GL[DIM];
int depth[DIM], path[DIM];
bool checked[DIM];

vector < pair<int,int> > sol;
int n, S, D;

int in(int node) {

    return node << 1;
}

int out(int node) {

    return (node << 1) + 1;
}

void readData() {

    scanf("%d", &n);
    S = 0; D = 2 * n + 2;
    for(int i = 1; i <= n; ++i) {

        int x, y; scanf("%d%d", &x, &y);
        int nodeIn = in(i), nodeOut = out(i);
        G[S].push_back(nodeIn); G[nodeIn].push_back(S);
        cap[S][nodeIn] = x;

        G[nodeOut].push_back(D); G[D].push_back(nodeOut);
        cap[nodeOut][D] = y;
    }

    for(int i = 1; i <= n; ++i)
        for(int j = i + 1; j <= n; ++j) {

            int nodeIn = in(i), nodeOut = out(j);
            G[nodeIn].push_back(nodeOut); G[nodeOut].push_back(nodeIn);
            cap[nodeIn][nodeOut] = 1;

            nodeIn = in(j), nodeOut = out(i);
            G[nodeIn].push_back(nodeOut); G[nodeOut].push_back(nodeIn);
            cap[nodeIn][nodeOut] = 1;
        }
}

bool buildGL() {

    for(int i = S; i <= D; ++i)
        checked[i] = false;

    int node = S;
    q.push(node); checked[node] = true; depth[node] = 0;
    while(!q.empty()) {

        int node = q.front(); q.pop();
        for(int nxt : G[node])
            if(!checked[nxt] && cap[node][nxt] > 0) {

                q.push(nxt); checked[nxt] = true; depth[nxt] = depth[node] + 1;
            }
    }

    for(int i = S; i <= D; ++i)
        GL[i].clear();

    for(int i = S; i <= D; ++i)
        for(int j : G[i])
            if(depth[i] - depth[j] == -1 && cap[i][j] > 0)
                GL[i].push_back(j);
    return checked[D];
}

int DFS(int node) {

    checked[node] = true; path[depth[node]] = node;
    if(node == D)
        return MAX_INF;
    else {

        for(int nxt : GL[node])
            if(!checked[nxt] && cap[node][nxt] > 0) {

                int x = DFS(nxt);
                if(x > 0)
                    return min(x, cap[node][nxt]);
            }
        return 0;
    }
}

void pushFlow() {

    for(int i = S; i <= D; ++i)
        checked[i] = false;

    int flow = DFS(S);
    while(flow) {

        for(int i = 0; i < depth[D]; ++i) {

            cap[path[i]][path[i + 1]] -= flow;
            cap[path[i + 1]][path[i]] += flow;
        }
        for(int i = S; i <= D; ++i)
            checked[i] = false;
        flow = DFS(S);
    }
}

void constructSol() {

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            if(i != j && cap[in(i)][out(j)] == 0)
                sol.push_back(make_pair(i, j));
}

void writeData() {

    printf("%d\n", (int)sol.size());
    for(pair <int,int> p : sol)
        printf("%d %d\n", p.first, p.second);
}

int main() {

    readData();
    while(buildGL())
        pushFlow();
    constructSol();
    writeData();
    return 0;
}
