/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <utility>

using std::pair;
using std::queue;
using std::vector;
using std::make_pair;

FILE *fin = freopen("import.in", "r", stdin);
FILE *fout = freopen("import.out", "w", stdout);

const int MAX_N = 1 + 221;
const int MAX_INF = 2000000000;
const int source = 0;

/*-------- Input data --------*/
int N, M, K;
vector<int > graph[MAX_N];
/*-------- Bellman Ford --------*/
vector< pair<int, int > > bf_graph[MAX_N];

int min_dist[MAX_N];
bool in_queue[MAX_N];
queue<int > my_queue;
/*-------- Solution --------*/
int profit[MAX_N];
/*-------- --------*/

void ReadInput() {
    scanf("%d%d%d", &N, &M, &K);
    for(int i = 1; i < N; i++) {
        int a, b; scanf("%d%d", &a, &b);
        graph[a].push_back(b); graph[b].push_back(a);
    }
    for(int i = 1; i <= M; i++) {
        int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);

        if(d == 0) {  //  Alfatrans
            bf_graph[b].push_back(make_pair(a, -c));
        } else {  //  Betatrans
            bf_graph[a].push_back(make_pair(b, c - 1));
        }
    }
}

void RunBellmanFord() {
    min_dist[source] = 0;
    my_queue.push(source);

    while(!my_queue.empty()) {
        int node = my_queue.front(); my_queue.pop();
        in_queue[node] = false;

        for(pair<int, int > edge : bf_graph[node]) {
            if(min_dist[node] + edge.second < min_dist[edge.first]) {
                min_dist[edge.first] = min_dist[node] + edge.second;
                if(!in_queue[edge.first]) {
                    my_queue.push(edge.first);
                    in_queue[edge.first] = true;
                }
            }
        }
    }
}

void DFS(int node = 1, int father = -1) {
    if(node != 1) {
        if(node >= K + 1 && father == 1) {
            profit[node] = min_dist[node];
        } else {
            profit[node] = min_dist[node] - min_dist[father];
        }
    } else {
        profit[node] = min_dist[node];  //  Pentru nodul 1
    }

    for(int son : graph[node]) {
        if(son != father) {
            DFS(son, node);
        }
    }
}

void SolveInequations() {
    //  Rezolvam inecuatiile aducandu-le pe toate la forma x - y <= k (k constant), apoi executand Bellman Ford pe graful obtinut

    for(int i = 1; i <= N; i++) {
        bf_graph[source].push_back(make_pair(i, 0));  //  Adaugam muchii de cost 0 de la sursa la fiecare nod
        min_dist[i] = MAX_INF;
    }
    RunBellmanFord();

    for(int i = K + 1; i <= N; i++) {
        min_dist[i] = -min_dist[i];
    }
    DFS();
}

void WriteOutput() {
    for(int i = 1; i <= N; i++) {
        printf("%d ", profit[i]);
    }
}

int main() {
    ReadInput();
    SolveInequations();
    WriteOutput();
    return 0;
}
