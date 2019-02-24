/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("cc.in", "r", stdin);
FILE *fout = freopen("cc.out", "w", stdout);

const int MAX_N = 2 * (1 + 100);
const int MAX_INF = 0x3fffffff;

/*----------------------------------------*/
int cap[MAX_N][MAX_N], cost[MAX_N][MAX_N];
int N;
/*----------------------------------------*/
vector< int > graph[MAX_N];
queue< int > Q;
bool inQueue[MAX_N];
int dmin[MAX_N], before[MAX_N];

int total_Cost = 0;
/*----------------------------------------*/


void read_Data() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            scanf("%d", &cost[i][N + j]);
            cost[N + j][i] = -cost[i][N + j];
        }
    }
}

void make_Graph() {
    const int S = 0;
    const int D = 2 * N + 1;

    for(int i = 1; i <= N; i++) {
        graph[S].push_back(i); graph[i].push_back(S);
        cap[S][i] = 1;
    }

    for(int i = 1; i <= N; i++) {
        for(int j = N + 1; j <= N + N; j++) {
            graph[i].push_back(j); graph[j].push_back(i);
            cap[i][j] = 1;
        }
    }

    for(int i = N + 1; i <= N + N; i++) {
        graph[i].push_back(D); graph[D].push_back(i);
        cap[i][D] = 1;
    }
}

bool bellman_Ford() {
    const int S = 0;
    const int D = 2 * N + 1;

    for(int i = S; i <= D; i++) {
        dmin[i] = MAX_INF;
    }
    dmin[S] = 0; Q.push(S);

    while(!Q.empty()) {
        int node = Q.front(); Q.pop(); inQueue[node] = false;

        for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
            if(cap[node][*it] && dmin[node] + cost[node][*it] < dmin[*it]) {
                before[*it] = node;
                dmin[*it] = dmin[node] + cost[node][*it];
                if(!inQueue[*it]) {
                    Q.push(*it); inQueue[*it] = true;
                }
            }
        }
    }

    if(dmin[D] == MAX_INF) {
        return false;
    } else {
        total_Cost += dmin[D];

        for(int node = D; node != S; node = before[node]) {
            cap[before[node]][node]--;
            cap[node][before[node]]++;
        }

        return true;
    }
}


int main() {
    read_Data();
    make_Graph();
    while(bellman_Ford());
    printf("%d", total_Cost);
    return 0;
}
