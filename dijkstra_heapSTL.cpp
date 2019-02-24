/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("dijkstra.in", "r", stdin);
FILE *fout = freopen("dijkstra.out", "w", stdout);

const int MAX_N = 1 + 50000;
const int MAX_INF = 0x3fffffff;

struct Edge {
    int vertex, cost;
    Edge(const int &vertex, const int &cost) {
        this->vertex = vertex; this->cost = cost;
    }
    bool operator <(const Edge &other) const{
        return this->cost > other.cost;
    }
};

vector <Edge> G[MAX_N];
int n, m;

priority_queue <Edge> pq;
int dist[MAX_N];

void readData() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i) {
        int u, v, c; scanf("%d%d%d", &u, &v, &c);
        G[u].push_back(Edge(v, c));
    }
}

void dijkstra() {

    for(int i = 1; i <= n; ++i) {
        dist[i] = MAX_INF;
    }
    pq.push(Edge(1, 0));

    while(!pq.empty()) {
        Edge edge = pq.top(); pq.pop();

        if(dist[edge.vertex] != MAX_INF) {
            continue;
        }
        else {
            dist[edge.vertex] = edge.cost;
            for(vector <Edge>::iterator it = G[edge.vertex].begin(); it != G[edge.vertex].end(); ++it)
                if(dist[it->vertex] == MAX_INF) {
                    pq.push(Edge(it->vertex, dist[edge.vertex] + it->cost));
                }
        }
    }
}

void writeData() {
    for(int i = 2; i <= n; ++i) {
        if(dist[i] != MAX_INF) {
            printf("%d ", dist[i]);
        }
        else {
            printf("0 ");
        }
    }
}

int main() {

    readData();
    dijkstra();
    writeData();
    return 0;
}
