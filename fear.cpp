/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("fear.in", "r", stdin);
FILE *fout = freopen("fear.out", "w", stdout);

const int MAX_N = 1 + 200;
const int MAX_FEAR = 2147483647;

/*-------------------------*/
int N, M;
vector< int > graph[MAX_N];
/*-------------------------*/ /** Max flow */
double cap[MAX_N][MAX_N];
int father[MAX_N];
queue< int > Q;
/*-------------------------*/

void readData() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        double fear; scanf("%lf", &fear);
        cap[u][v] = cap[v][u] = fear;
        graph[u].push_back(v); graph[v].push_back(u);
    }
}

bool BFS() {
    while(!Q.empty()) {Q.pop();}

    const int source = 1;
    const int destination = N;

    for(int i = 1; i <= N; i++) {
        father[i] = -1;
    }
    father[source] = 0; Q.push(source);
    while(!Q.empty()) {
        int node = Q.front(); Q.pop();
        for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
            if(father[*it] == -1 && cap[node][*it] > 1) {
                father[*it] = node;
                if(*it == destination) {
                    return true;
                }
                Q.push(*it);
            }
        }
    }

    return false;
}

void getFlow() {
    const int source = 1;
    const int destination = N;

    double answer = 1;
    while(BFS()) {
        double fear = (double)MAX_FEAR;
        for(int node = destination; node != source; node = father[node]) {
            fear = min(fear, cap[father[node]][node]);
        }
        for(int node = destination; node != source; node = father[node]) {
            cap[father[node]][node] /= fear;
            cap[node][father[node]] *= fear;
        }
        answer *= fear;
    }
    printf("%.6f", answer);
}

int main() {
    readData();
    getFlow();
    return 0;
}
