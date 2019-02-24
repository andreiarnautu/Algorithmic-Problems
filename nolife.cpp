/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("nolife.in", "r", stdin);
FILE *fout = freopen("nolife.out", "w", stdout);

const int MAX_N = 1 + 100000;
const int bufferDim = 100000;
const int MAX_INF = 0x3fffffff;

struct Edge {
    int u, v, cost;
    Edge(const int &u, const int &v, const int &cost) {
        this->u = u; this->v = v; this->cost = cost;
    }
    bool operator <(const Edge &other) const {
        return this->cost > other.cost;
    }
};

vector <Edge> G[MAX_N];
int n, m;

priority_queue <Edge> pq_1, pq_2;
int dmin_1[MAX_N], dmin_2[MAX_N];
int before_1[MAX_N], before_2[MAX_N];

vector <int> nodes;
vector <int> path_1, path_2;
vector <int> marked;

void readData() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i) {
        int u, v, c; scanf("%d%d%d", &u, &v, &c);
        G[u].push_back(Edge(u, v, c));
        G[v].push_back(Edge(v, u, c));
    }
}

void initialize(int u, int v) {

    for(int i = 0; i < (int)marked.size(); ++i) {
      dmin_1[marked[i]] = dmin_2[marked[i]] = MAX_INF;
    }
    while(!pq_1.empty()) {
        pq_1.pop();
    }
    while(!pq_2.empty()) {
        pq_2.pop();
    }

    pq_1.push(Edge(u, MAX_INF, 0));
    pq_2.push(Edge(v, MAX_INF, 0));
    path_1.clear();
    path_2.clear();
    nodes.clear();
    marked.clear();
}

void nextDijkstraStep() {

    /* mai adaugam un nod pentru care avem distanta minima calculata, pentru fiecare din cele 2 noduri de pornire */
    if(!pq_1.size() || !pq_2.size())
        return;


    Edge edge = pq_1.top(); pq_1.pop();

    while(!pq_1.empty() && dmin_1[edge.u] != MAX_INF) {
        edge = pq_1.top(); pq_1.pop();
    }

    if(dmin_1[edge.u] != MAX_INF) {
        return;
    }

    marked.push_back(edge.u);
    dmin_1[edge.u] = edge.cost;
    before_1[edge.u] = edge.v;

    for(vector <Edge>::iterator it = G[edge.u].begin(); it != G[edge.u].end(); ++it)
        if(dmin_1[it->v] == MAX_INF) {
            pq_1.push(Edge(it->v, it->u, it->cost + edge.cost));
        }

    if(dmin_2[edge.u] != MAX_INF) {
        /* daca s-a ajuns si din celalalt nod cu parcurgerea in acest nod */
        nodes.push_back(edge.u);
    }

    /*----------------------------------------------------------*/

    /* facem aceiasi pasi si pentru parcurgerea din nodul secund */

    edge = pq_2.top(); pq_2.pop();
    while(!pq_2.empty() && dmin_2[edge.u] != MAX_INF) {
        edge = pq_2.top(); pq_2.pop();
    }
    if(dmin_2[edge.u] != MAX_INF) {
        return;
    }

    marked.push_back(edge.u);
    dmin_2[edge.u] = edge.cost;
    before_2[edge.u] = edge.v;

    for(vector <Edge>::iterator it = G[edge.u].begin(); it != G[edge.u].end(); ++it)
        if(dmin_2[it->v] == MAX_INF) {
            pq_2.push(Edge(it->v, it->u, it->cost + edge.cost));
        }

    if(dmin_1[edge.u] != MAX_INF) {
        nodes.push_back(edge.u);
    }
}

void getPath(int u, int v, int node) {

    int current = node;

    while(current != u) {
        path_1.push_back(current);
        current = before_1[current];
    }
    path_1.push_back(current);

    current = node;
    while(current != v) {
        path_2.push_back(current);
        current = before_2[current];
    }
    path_2.push_back(current);
}

void writePath() {
    printf("%d ", (int)path_1.size() + (int)path_2.size() - 1);
    for(int i = (int)path_1.size() - 1; i >= 0; --i)
        printf("%d ", path_1[i]);
    for(int i = 1; i < (int)path_2.size(); ++i)
        printf("%d ", path_2[i]);
    printf("\n");
}

int main() {

    readData();
    int q;

    for(int i = 0; i < n; ++i) {
        dmin_1[i] = dmin_2[i] = MAX_INF;
    }

    for(scanf("%d", &q); q; --q) {
        int u, v; scanf("%d%d", &u, &v);
        initialize(u, v);

        int steps = 0;
        for(;steps <= 60; steps++) {
            nextDijkstraStep();
        }


        int node = -1, dmin = MAX_INF;
        for(int i = 0; i < (int)nodes.size(); ++i)
            if(dmin > dmin_1[nodes[i]] + dmin_2[nodes[i]]) {
                node = nodes[i];
                dmin = dmin_1[nodes[i]] + dmin_2[nodes[i]];
            }

        if(node == -1) {
            printf("0\n");
            continue;
        }
        getPath(u, v, node);
        writePath();
    }
    return 0;
}
