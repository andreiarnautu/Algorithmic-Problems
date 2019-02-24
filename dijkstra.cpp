/**
  *  Worg
  */
#include <queue>
#include <vector>
#include <cstdio>

using std::vector;
using std::priority_queue;

FILE *fin = freopen("dijkstra.in", "r", stdin);
FILE *fout = freopen("dijkstra.out", "w", stdout);

const int kMaxN = 1 + 50000;
const int kMaxInf = 2000000000;

/*-------- Structures --------*/
struct Edge {
    int node, dist;
    Edge(const int _node, const int _dist) {
        this->node = _node; this->dist = _dist;
    }
    bool operator <(const Edge &other) const {
        return this->dist > other.dist;
    }
};
/*-------- Input data --------*/
int N, M;
vector<Edge > graph[kMaxN];
/*-------- Dijkstra --------*/
int min_dist[kMaxN];
priority_queue<Edge > heap;
/*-------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= M; i++) {
        int u, v, dist; scanf("%d%d%d", &u, &v, &dist);
        graph[u].push_back(Edge(v, dist));
    }
}

void DijkstraAlgorithm() {
    for(int i = 1; i <= N; i++) {
        min_dist[i] = kMaxInf;
    }

    heap.push(Edge(1, 0));
    while(!heap.empty()) {
        Edge edge = heap.top(); heap.pop();

        if(min_dist[edge.node] == kMaxInf) {
            min_dist[edge.node] = edge.dist;
            for(Edge next_edge : graph[edge.node]) {
                if(min_dist[next_edge.node] == kMaxInf) {
                    heap.push(Edge(next_edge.node, edge.dist + next_edge.dist));
                }
            }
        }
    }
}

void WriteOutput() {
    for(int i = 2; i <= N; i++) {
        if(min_dist[i] == kMaxInf) {
            printf("0 ");
        } else {
            printf("%d ", min_dist[i]);
        }
    }
}

int main() {
    ReadInput();
    DijkstraAlgorithm();
    WriteOutput();
    return 0;
}
