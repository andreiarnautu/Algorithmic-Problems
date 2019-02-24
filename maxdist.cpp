/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <bitset>
#include <cstdlib>

using namespace std;
FILE *fin = freopen("maxdist.in", "r", stdin);
FILE *fout = freopen("maxdist.out", "w", stdout);

const int MAX_N = 1 + 500000;
const int MAX_LOG = 20 + 2;

/*------------------------*/
int N, Q;
int queryNode[MAX_N];
vector< int > graph[MAX_N];
bitset< MAX_N > Marked(0);
/*------------------------*/
queue< int > Queue;
int depth[MAX_N];
int ancestor[MAX_N][MAX_LOG];
/*------------------------*/
int Solution[MAX_N][2];
/*------------------------*/

void readInput() {
    scanf("%d%d", &N, &Q);
    for(int i = 1; i < N; i++) {
        int u, v; scanf("%d%d", &u, &v);
        graph[u].push_back(v); graph[v].push_back(u);
    }
    for(int i = 1; i <= Q; i++) {
        scanf("%d", &queryNode[i]);
        Marked[queryNode[i]] = true;
    }
}

void BFS(int node = 1, int father = 0) {
    Queue.push(1); depth[1] = 1;
    while(!Queue.empty()) {
        int node = Queue.front(); Queue.pop();
        for(int nxt : graph[node]) {
            if(!depth[nxt]) {
                depth[nxt] = depth[node] + 1;
                ancestor[nxt][0] = node;
                Queue.push(nxt);
            }
        }
    }
}

int getLCA(int u, int v) {
    if(depth[u] < depth[v]) {
        swap(u, v);
    }

    for(int i = MAX_LOG - 1; i >= 0; i--) {
        if(depth[u] - (1 << i) >= depth[v]) {
            u = ancestor[u][i];
        }
    }
    if(u == v) {
        return u;
    } else {
        for(int i = MAX_LOG - 1; i >= 0; i--) {
            if(ancestor[u][i] > 0 && ancestor[v][i] > 0 && ancestor[u][i] != ancestor[v][i]) {
                u = ancestor[u][i];
                v = ancestor[v][i];
            }
        }
        return ancestor[u][0];
    }
}

int getNodeDistance(int u, int v) {
    int Answer = getLCA(u, v);
    return (depth[u] - depth[Answer]) + (depth[v] - depth[Answer]);
}

void updateNodes(int &x, int &y, int &bestDist, int &node) {
    int distA = getNodeDistance(node, x);
    int distB = getNodeDistance(node, y);

    int newX = x;
    int newY = y;
    if(distA > bestDist) {
        newX = x; newY = node;
        bestDist = distA;
    }
    if(distB > bestDist) {
        newX = y; newY = node;
        bestDist = distB;
    }

    x = newX;
    y = newY;
}

void solveNormal() {
    Solution[1][1] = 0;
    int x = queryNode[1];
    int y = queryNode[2];
    int bestDist = getNodeDistance(x, y);
    Solution[2][1] = bestDist;

    for(int i = 3; i <= Q; i++) {
        updateNodes(x, y, bestDist, queryNode[i]);
        Solution[i][1] = bestDist;
    }
}

void solveReversed() {
    int x = 0;
    int y = 0;
    int bestDist = 0;


    for(int i = 1; i <= N; i++) {
        if(!Marked[i]) {
            if(!x) {
                x = i;
            } else if(!y) {
                y = i;
                bestDist = getNodeDistance(x, y);
            } else {
                updateNodes(x, y, bestDist, i);
            }
        }
    }

    for(int i = Q; i >= 1; i--) {
        Solution[i][0] = bestDist;
        if(!x) {
            x = queryNode[i];
        } else if(!y) {
            y = queryNode[i];
            bestDist = getNodeDistance(x, y);
        } else {
            updateNodes(x, y, bestDist, queryNode[i]);
        }
    }
}

void writeOutput() {
    for(int i = 1; i <= Q; i++) {
        printf("%d %d\n", Solution[i][0], Solution[i][1]);
    }
}

int main() {
    readInput();
    BFS();
    for(int i = 1; (1 << i) <= N; i++) {
        for(int j = 1; j <= N; j++) {
            ancestor[j][i] = ancestor[ancestor[j][i - 1]][i - 1];
        }
    }
    solveNormal();
    solveReversed();
    writeOutput();
    return 0;
}
