/**
  *  Worg
  */
#include <set>
#include <stack>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("obiective.in", "r", stdin);
FILE *fout = freopen("obiective.out", "w", stdout);

const int MAX_N = 1 + 32000;
const int MAX_LOG = 17;

/*--------------------------*/ /** General data */
vector< int > graph[MAX_N];
int M, N;
/*--------------------------*/ /** SCC */
int lowlink[MAX_N], index[MAX_N], sccIndex[MAX_N];
int currentIndex = 1, sccCount;

bool inStack[MAX_N];
stack< int > Stack;
/*--------------------------*/ /** Tree stuff + LCA */
set< int > sccGraph[MAX_N];
int ancestor[MAX_LOG][MAX_N];

bool checked[MAX_N];
int RMQ[MAX_LOG][MAX_N << 1];
int lg[MAX_N << 1], first[MAX_N];
int eulerianIndex;
/*--------------------------*/


void readData() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        graph[u].push_back(v);
    }
}

void strongConnect(int node) {
    index[node] = lowlink[node] = currentIndex++;
    Stack.push(node); inStack[node] = true;
    for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
        if(!index[*it]) {
            strongConnect(*it);
            lowlink[node] = min(lowlink[node], lowlink[*it]);
        } else if(inStack[*it]) {
            lowlink[node] = min(lowlink[node], index[*it]);
        }
    }

    if(lowlink[node] == index[node]) {
        sccCount++;
        int now;
        do {
            now = Stack.top(); Stack.pop();
            sccIndex[now] = sccCount; inStack[now] = false;
        }while(now != node);
    }
}

void runTarjan() {
    for(int i = 1; i <= N; i++) {
        if(!index[i]) {
            strongConnect(i);
        }
    }
}

void buildTree() {
    for(int i = 1; i <= N; i++) {
        sccIndex[i] = sccCount - sccIndex[i] + 1;
    }
    for(int i = 1; i <= sccCount; i++) {
        ancestor[0][i] = i;
    }
    for(int i = 1; i <= N; i++) {
        for(vector< int >::iterator it = graph[i].begin(); it != graph[i].end(); it++) {
            if(sccIndex[i] != sccIndex[*it]) {
                sccGraph[sccIndex[i]].insert(sccIndex[*it]);
                ancestor[0][sccIndex[*it]] = min(ancestor[0][sccIndex[*it]], sccIndex[i]);
            }
        }
    }
}

void DFS(int node) {
    checked[node] = true;
    RMQ[0][++eulerianIndex] = node;
    first[node] = eulerianIndex;
    for(set< int >::iterator it = sccGraph[node].begin(); it != sccGraph[node].end(); it++) {
        if(!checked[*it]) {
            DFS(*it);
            RMQ[0][++eulerianIndex] = node;
            ancestor[0][node] = min(ancestor[0][node], ancestor[0][*it]);
        }
    }
}

void buildData() {
    DFS(1);
    for(int i = 2; i <= (N << 1); i++) {
        lg[i] = lg[i >> 1] + 1;
    }
    for(int i = 1; i <= lg[sccCount]; i++) {
        for(int j = 1; j <= sccCount; j++) {
            ancestor[i][j] = ancestor[i - 1][ancestor[i - 1][j]];
        }
    }
    for(int i = 1; i <= lg[eulerianIndex]; i++) {
        const int LIMIT = eulerianIndex - (1 << i) + 1;
        for(int j = 1; j <= LIMIT; j++) {
            RMQ[i][j] = min(RMQ[i - 1][j], RMQ[i - 1][j + (1 << (i - 1))]);
        }
    }
}

int LCA(int u, int v) {
    u = first[u]; v = first[v];
    if(u > v) {
        swap(u, v);
    }
    int level = lg[v - u + 1];
    return min(RMQ[level][u], RMQ[level][v - (1 << level) + 1]);
}

void solveQueries() {
    int T;
    for(scanf("%d", &T); T; T--) {
        int u, v; scanf("%d%d", &u, &v);
        u = sccIndex[u]; v = sccIndex[v];

        int lca = LCA(u, v);
        if(u == lca) {
            printf("0\n");
        } else {
            int answer = 1;
            for(int i = lg[sccCount]; i >= 0; i--) {
                if(ancestor[i][u] > lca) {
                    answer += (1 << i);
                    u = ancestor[i][u];
                }
            }
            printf("%d\n", answer);
        }
    }
}

int main() {
    readData();
    runTarjan();
    buildTree();
    buildData();
    solveQueries();
    return 0;
}
