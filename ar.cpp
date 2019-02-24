/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("ar.in", "r", stdin);
FILE *fout = freopen("ar.out", "w", stdout);

const int MAX_N = 1 + 20000;
const int bufferDim = 100000;

/*-------- Input reader --------*/
class inputReader {
private:
        char buffer[bufferDim];
        int pos = 0;

        bool digit(char c) {
            return('0' <= c && c <= '9');
        }
public:
        void getBuffer() {
            fread(buffer, 1, bufferDim, stdin);
            pos = 0;
        }

        void operator >>(int &nr) {
            nr = 0;
            while(!digit(buffer[pos]))
                if(++ pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++ pos == bufferDim)
                    getBuffer();
            }
        }
} cin;
/*-------- Input data --------*/
struct Edge {
    int u, v;

    Edge(const int &u, const int &v) {
        this->u = u; this->v = v;
    }
};

int N, M, R;
int degree[MAX_N];
vector< Edge > Edges;
/*-------- Bipartite graph --------*/
vector< int > graph[MAX_N];
vector< int > redNodes;

bool checked[MAX_N];
int left[MAX_N], right[MAX_N];

int Cuplaj;
/*-------- Answer --------*/
bool hasSolution = true;
vector< Edge > Solution;
/*-------- --------*/

void readInput() {
    cin.getBuffer();
    cin >> N; cin >> M; cin >> R;
    for(int i = 1; i <= M; i++) {
        int u, v; cin >> u; cin >> v;
        Edges.push_back(Edge(u, v));
        degree[u] ++; degree[v] ++;
    }
}

void deleteRedEdges() {
    for(Edge edge : Edges) {
        if(degree[edge.u] == R && degree[edge.v] == R) {
            Solution.push_back(edge);
            degree[edge.u] --; degree[edge.v] --;
        }
    }
}

bool redBlackEdge(const Edge &edge) {
    return((degree[edge.u] == R && degree[edge.v] == R - 1) ||
           (degree[edge.u] == R - 1 && degree[edge.v] == R));
}

void makeGraph() {
    for(Edge edge : Edges) {
        if(redBlackEdge(edge)) {
            graph[edge.u].push_back(edge.v);
            graph[edge.v].push_back(edge.u);
        }
    }

    for(int node = 1; node <= N; node++) {
        if(degree[node] == R) {
            redNodes.push_back(node);
        }
    }
}

bool pairUp(int node) {
    if(checked[node]) {
        return false;
    } else {
        checked[node] = true;
    }

    for(int blackNode : graph[node]) {
        if(!right[blackNode]) {
            left[node] = blackNode;
            right[blackNode] = node;
            Cuplaj ++;
            return true;
        }
    }

    for(int blackNode : graph[node]) {
        if(pairUp(right[blackNode])) {
            left[node] = blackNode;
            right[blackNode] = node;
            return true;
        }
    }

    return false;
}

void runHopcroftCarp() {
    bool ok;
    do {
        ok = false;
        for(int node : redNodes) {
            checked[node] = false;
        }
        for(int node : redNodes) {
            if(!left[node]) {
                ok |= pairUp(node);
            }
        }
    }while(ok);

    for(int node : redNodes) {
        if(left[node]) {
            Solution.push_back(Edge(node, left[node]));
        }
    }
}

void writeOutput() {
    if(Cuplaj < (int)redNodes.size()) {
        printf("-1");
    } else {
        printf("%d\n", (int)Solution.size());
        for(Edge edge : Solution) {
            printf("%d %d\n", edge.u, edge.v);
        }
    }
}

int main() {
    readInput();
    deleteRedEdges();
    makeGraph();
    runHopcroftCarp();
    writeOutput();
    return 0;
}
