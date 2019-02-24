/**
  *  Worg
  */
#include <stack>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("fotbal2.in", "r", stdin);
FILE *fout = freopen("fotbal2.out", "w", stdout);

const int MAX_N = 1 + 50000 + 1;
const int MAX_EDGES = 200000;

/*--------------------*/
int N, M;
/*--------------------*/
vector< pair< int,int > > graph[MAX_N];
int degree[MAX_N], crtPoints[MAX_N], crtEdgeIndex;

int matchIndex[MAX_EDGES];
bool checked[MAX_EDGES];
/*--------------------*/
int Winner[MAX_N];
int Result;
/*--------------------*/


void addEdge(int u, int v, int index = 0) {
    crtEdgeIndex++;
    graph[u].push_back(make_pair(v, crtEdgeIndex));
    graph[v].push_back(make_pair(u, crtEdgeIndex));
    matchIndex[crtEdgeIndex] = index;

    degree[u]++; degree[v]++;
}

void readInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        addEdge(u, v, i);
    }
}

void addEdges() {
    for(int i = 1; i <= N; i++) {
        if(degree[i] % 2 == 1) {
            addEdge(i, N + 1);
            Result = 2;
        } else {
           // addEdge(i, N + 1); addEdge(i, N + 1);
        }
    }

}

int deleteNext(const int Node) {
    while(!graph[Node].empty() && checked[graph[Node].back().second]) {
        graph[Node].pop_back();
    }

    pair< int,int > Pair = graph[Node].back();

    int nextNode = Pair.first;
    checked[Pair.second] = true;
    Winner[matchIndex[Pair.second]] = Node;
    graph[Node].pop_back();

    degree[Node]--; degree[nextNode]--;
    return nextNode;
}

void eulerianCycle(const int Node) {
    while(degree[Node]) {
        int nxtNode = deleteNext(Node);
        eulerianCycle(nxtNode);
    }
}

void writeOutput() {
    printf("%d\n", Result);
    for(int i = 1; i <= M; i++) {
        printf("%d\n", Winner[i]);
    }
}

int main() {
    readInput();
    addEdges();
    for(int i = 1; i <= N; i++) {
        if(degree[i]) {
            eulerianCycle(i);
        }
    }
    writeOutput();

    return 0;
}
