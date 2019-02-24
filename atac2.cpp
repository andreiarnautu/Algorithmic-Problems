/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("atac2.in", "r", stdin);
FILE *fout = freopen("atac2.out", "w", stdout);

const int MAX_N = 1 + 10000;
const int MAX_U = 200;
const int MAX_INF = 0x3fffffff;
const int S = 150;
const int D = 151;

/*-------------------------*/ /** General */
int N, M, U, X;
int index[MAX_N];
vector< int > graph[MAX_N];
/*-------------------------*/ /** BFS */
int dist[MAX_N];
queue< int > Q;
/*-------------------------*/ /** Bipartite graph */
vector< int > bGraph[MAX_N];
int cap[MAX_U][MAX_U], cost[MAX_U][MAX_U];
/*-------------------------*/ /** Min Cost Max Flow */
int dmin[MAX_U], before[MAX_U];
bool inQueue[MAX_U];
/*-------------------------*/
void readData() {
    scanf("%d%d%d%d", &N, &M, &U, &X);
    for(int i = 1; i <= U; i++) {
        int node; scanf("%d", &node);
        index[node] = i;
    }
    for(int i = 1; i <= M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        graph[u].push_back(v); graph[v].push_back(u);
    }
}

void calcDist(int node) {
    for(int i = 1; i <= N; i++) {
        dist[i] = MAX_INF;
    }
    dist[node] = 0; Q.push(node);

    while(!Q.empty()) {
        int now = Q.front(); Q.pop();
        for(vector< int >::iterator it = graph[now].begin(); it != graph[now].end(); it++) {
            if(dist[*it] == MAX_INF) {dist[*it] = dist[now] + 1; Q.push(*it);}
        }
    }
}

void constructBipartiteGraph() {
    int crtIndex = U;
    for(vector< int >::iterator it = graph[X].begin(); it != graph[X].end(); it++) {
        calcDist(*it);
        crtIndex++;
        for(int i = 1; i <= N; i++) {
            if(index[i]) {
                bGraph[index[i]].push_back(crtIndex); bGraph[crtIndex].push_back(index[i]);
                cap[index[i]][crtIndex] = 1;
                cost[index[i]][crtIndex] = dist[i]; cost[crtIndex][index[i]] = -dist[i];
            }
        }
    }

    for(int i = 1; i <= U; i++) {
        bGraph[S].push_back(i); bGraph[i].push_back(S);
        cap[S][i] = 1;
    }
    for(int i = U + 1; i <= crtIndex; i++) {
        bGraph[i].push_back(D); bGraph[D].push_back(i);
        cap[i][D] = 1;
    }

}

bool bellmanFord(int &totalCost) {
    for(int i = 1; i <= D; i++) {
        dmin[i] = MAX_INF;
    }
    dmin[S] = 0; Q.push(S);
    while(!Q.empty()) {
        int node = Q.front(); Q.pop(); inQueue[node] = false;
        for(vector< int >::iterator it = bGraph[node].begin(); it != bGraph[node].end(); it++) {
            if(cap[node][*it] && dmin[*it] > dmin[node] + cost[node][*it]) {
                dmin[*it] = dmin[node] + cost[node][*it];
                before[*it] = node;
                if(!inQueue[*it]) {Q.push(*it); inQueue[*it] = true;}
            }
        }
    }
    if(dmin[D] == MAX_INF) {
        return false;
    } else {
        int flow = MAX_INF;
        for(int node = D; node != S; node = before[node]) {
            flow = min(flow, cap[before[node]][node]);
        }
        for(int node = D; node != S; node = before[node]) {
            totalCost += cost[before[node]][node] * flow;
            cap[before[node]][node] -= flow;
            cap[node][before[node]] += flow;
        }

        return true;
    }
}

int minCostMaxFlow() {
    int totalCost = 0;
    while(bellmanFord(totalCost));
    return totalCost;
}

int main() {
    readData();
    constructBipartiteGraph();
    printf("%d", minCostMaxFlow());
    return 0;
}
