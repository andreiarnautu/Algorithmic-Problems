/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("copsamica.in", "r", stdin);
FILE *fout = freopen("copsamica.out", "w", stdout);

const int MAX_N = 1 + 1000;
const int MAX_D = 1 + 20000;

/*-------- Input Data --------*/
int testCount;
int N;
int dmax[MAX_N][MAX_N];
/*-------- Cycle solving --------*/
struct Edge {
    int u, v;
    int value;

    Edge(const int &u, const int &v, const int &value) {
        this->u = u;
        this->v = v;
        this->value = value;
    }

    bool operator <(const Edge &other) const{
        if(this->value != other.value) {
            return this->value > other.value;
        } else if(this->u != other.u) {
            return this->u > other.u;
        } else {
            return this->v > other.v;
        }
    }
};


vector< Edge > vec[MAX_D];
vector< Edge > Edges;
int degree[MAX_N];

vector< Edge > Solution;
/*-------- Disjoint sets --------*/
int father[MAX_N];
/*-------- --------*/


void readInput() {
    scanf("%d", &N);
    for(int i = 1; i < N; i++) {
        for(int j = i + 1; j <= N; j++) {
            scanf("%d", &dmax[i][j]);
        }
    }
}

int Group(int node) {
    if(node != father[node]) {
        father[node] = Group(father[node]);
    }
    return father[node];
}

void Unite(int u, int v) {
    degree[u] ++; degree[v] ++;
    u = Group(u);
    v = Group(v);
    father[u] = v;
}

void createEdges() {
    for(int i = 1; i <= N; i++) {
        for(int j = i + 1; j <= N; j++) {
            vec[dmax[i][j]].push_back(Edge(i, j, dmax[i][j]));
        }
    }
    for(int i = MAX_D - 1; i >= 1; i--) {
        for(Edge edge : vec[i]) {
            Edges.push_back(edge);
        }
    }
}

void initializeData() {
    for(int i = 1; i <= N; i++) {
        father[i] = i;
    }
    for(int i = 1; i <= N; i++) {
        degree[i] = 0;
    }
}

void solveCycle() {
    int edgeCount = 0;
    for(Edge edge : Edges) {
        if(degree[edge.u] != 2 && degree[edge.v] != 2 && Group(edge.u) != Group(edge.v)) {
            Solution.push_back(edge);
            Unite(edge.u, edge.v);
            edgeCount ++;

            if(edgeCount == N - 1) {
                break;
            }
        }
    }

    for(int i = 1; i <= N; i++) {
        if(degree[i] == 1) {
            for(int j = i + 1; j <= N; j++) {
                if(degree[j] == 1) {
                    Solution.push_back(Edge(i, j, 0));
                    return;
                }
            }
        }
    }
}

void writeOutput() {
    for(Edge edge : Solution) {
        printf("%d %d %d\n", edge.u, edge.v, edge.value);
    }
}

void clearData() {
    Edges.clear();
    Solution.clear();
    for(int i = MAX_D - 1; i >= 1; i--) {
        vec[i].clear();
    }
}

int main() {
    scanf("%d", &testCount);
    for(; testCount > 0; testCount --) {
        readInput();
        createEdges();
        initializeData();
        solveCycle();
        writeOutput();
        clearData();
    }

    return 0;
}
