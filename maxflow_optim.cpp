/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("maxflow.in", "r", stdin);
FILE *fout = freopen("maxflow.out", "w", stdout);

const int MAX_N = 1 + 1000;
const int MAX_M = 1 + 5000;
const int MAX_INF = 0x3fffffff;

struct Edge {
public:
    int left, right, cap;

    Edge() {
        this->left = this->right = this->cap = 0;
    }
    Edge(const int &left, const int &right, const int &cap) {
        this->left = left; this->right = right; this->cap = cap;
    }
};

/*-------------------------*/
int N, M;
vector< int > graph[MAX_N];
/*-------------------------*/
Edge Edges[MAX_M << 1];
int crtIndex = 1;
/*-------------------------*/
queue< int > Queue;
int father[MAX_N];
/*-------------------------*/

void makeEdge(int u, int v, int cap) {
    Edges[++crtIndex] = Edge(u, v, cap); graph[u].push_back(crtIndex);
    Edges[++crtIndex] = Edge(v, u, 0); graph[v].push_back(crtIndex);
}

void readData() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= M; i++) {
        int u, v, cap; scanf("%d%d%d", &u, &v, &cap);
        makeEdge(u, v, cap);
    }
}

bool BFS() {
    const int source = 1;
    const int destination = N;

    while(!Queue.empty()) { Queue.pop(); }

    for(int i = 1; i <= N; i++) {
        father[i] = -1;
    }
    father[source] = 0;

    Queue.push(source);
    while(!Queue.empty()) {
        int node = Queue.front(); Queue.pop();
        for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
            if(Edges[*it].cap > 0 && father[Edges[*it].right] == -1) {
                father[Edges[*it].right] = *it;
                if(Edges[*it].right == destination) {
                    return true;
                }
                Queue.push(Edges[*it].right);
            }
        }
    }
    return false;
}

int reversed(int val) {
    return val ^ 1;
}

int maxFlow() {
    const int source = 1;
    const int destination = N;
    int answer = 0;

    while(BFS()) {
        for(vector< int >::iterator it = graph[destination].begin(); it != graph[destination].end(); it++) {
            if(Edges[reversed(*it)].cap > 0 && father[Edges[*it].right] != -1) {
                int maxFlow = MAX_INF;
                father[destination] = reversed(*it); /* we want the path to include the current edge */

                for(int node = destination; node != source; node = Edges[father[node]].left) {
                    maxFlow = min(maxFlow, Edges[father[node]].cap);
                }
                answer += maxFlow;
                for(int node = destination; node != source; node = Edges[father[node]].left) {
                    Edges[father[node]].cap -= maxFlow;
                    Edges[reversed(father[node])].cap += maxFlow;
                }

            }
        }
    }

    return answer;
}

int main() {
    readData();
    printf("%d", maxFlow());
    return 0;
}
