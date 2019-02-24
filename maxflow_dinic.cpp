#include <queue>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 1000, MAX_INF = 0x3fffffff;

int n, m, totalFlow;

vector < int > G[1 + MAX_N];
int capacitate[1 + MAX_N][1 + MAX_N];

vector < int > GL[1 + MAX_N];
queue < int > coada;
bool vizitat[1 + MAX_N];
int adancime[1 + MAX_N], tata[1 + MAX_N];

bool buildGL() {

    for (int i = 1; i <= n; i++)
        vizitat[i] = false;

    int nod = 1;
    vizitat[nod] = true;
    coada.push(nod);
    adancime[nod] = 0;

    while (!coada.empty()) {

        nod = coada.front();
        coada.pop();
        for (int vecin : G[nod]) {
            if(capacitate[nod][vecin] > 0 && !vizitat[vecin]) {
                coada.push(vecin);
                vizitat[vecin] = true;
                adancime[vecin] = adancime[nod] + 1;
            }
        }
    }

    for (int i = 1; i <= n; i++)
        GL[i].clear();
    for (int nod = 1; nod <= n; nod++) {
        for (int vecin : G[nod]) {
            if (adancime[nod] - adancime[vecin] == -1 && capacitate[nod][vecin] > 0)
                GL[nod].push_back(vecin);
        }
    }

    return vizitat[n];
}

int drum[1 + MAX_N];

int DFS(int nod) {

    vizitat[nod] = true;
    drum[adancime[nod]] = nod;
    if (nod == n)
        return MAX_INF;
    else {
        for (int vecin : GL[nod])
            if (!vizitat[vecin] && capacitate[nod][vecin] > 0) {
                int dfs = DFS(vecin);
                if (dfs > 0)
                    return min(capacitate[nod][vecin], dfs);
            }
        return 0;
    }
}

void pushFlow() {

    for(int i = 1; i <= n; ++i)
        vizitat[i] = false;
    int flow = DFS(1);
    while (flow) {

        for (int i = 0; i < adancime[n]; ++i) {

            capacitate[drum[i]][drum[i + 1]] -= flow;
            capacitate[drum[i + 1]][drum[i]] += flow;
        }
        totalFlow += flow;
        for(int i = 1; i <= n; ++i)
            vizitat[i] = false;
        flow = DFS(1);
    }
}

int main() {

    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        capacitate[u][v] = c;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    while(buildGL())
        pushFlow();
  printf("%d\n", totalFlow);
  return 0;
}
