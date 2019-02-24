/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("arb2.in", "r", stdin);
FILE *fout = freopen("arb2.out", "w", stdout);

const int MAX_N = 1 + 100000;
const int bufferDim = 100000;
const int MAX_INF = 1000000000 + 1;

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

        void getInt(int &nr) {
            nr = 0;
            while(!digit(buffer[pos]))
                if(++pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == bufferDim)
                    getBuffer();
            }
        }
} cin;

struct Edge {
    int vertex, d, cost;
    Edge() {
        this->vertex = this->d = this->cost = 0;
    }
    Edge(const int &vertex, const int &d, const int &cost) {
        this->vertex = vertex; this->d = d; this->cost = cost;
    }
};
/*----------------------*/
int N;
vector<Edge> G[MAX_N];
/*----------------------*/
int dist[MAX_N], leafDist[MAX_N], degree[MAX_N];
Edge father[MAX_N];
/*----------------------*/
queue <int> q;
int cMin[MAX_N];
/*----------------------*/

void readData() {
    cin.getBuffer();
    cin.getInt(N);
    for(int i = 1; i < N; ++i) {
        int u, v, d, c;
        cin.getInt(u); cin.getInt(v); cin.getInt(d); cin.getInt(c);
        G[u].push_back(Edge(v, d, c)); G[v].push_back(Edge(u, d, c));
    }
}

void DFS(int node = 1) {
    for(vector<Edge>::iterator it = G[node].begin(); it != G[node].end(); ++it) {
        if(it->vertex != father[node].vertex) {
            degree[node]++;
            father[it->vertex] = Edge(node, it->d, it->cost);
            dist[it->vertex] = dist[node] + it->d;
            DFS(it->vertex);
            leafDist[node] = max(leafDist[node], leafDist[it->vertex] + it->d);
        }
    }
}

void solveTree(int root = 1) {
    for(int i = 1; i <= N; ++i) {
        if(!degree[i]) {
            q.push(i);
            cMin[i] = MAX_INF;
        } else {
            cMin[i] = 0;
        }
    }

    long long answer = 0;
    while(!q.empty()) {
        int node = q.front(); q.pop();
        if(node == root) {
            break;
        } else {
            int fatherID = father[node].vertex;
            cMin[node] = min(cMin[node], father[node].cost);
            cMin[fatherID] += cMin[node];
            answer += 1LL * cMin[node] * (leafDist[fatherID] - leafDist[node] - father[node].d);
            degree[fatherID]--;
            if(!degree[fatherID]) {
                q.push(fatherID);
            }
        }
    }
    printf("%lld", answer);
}

int main() {
    readData();
    DFS();
    solveTree();
    return 0;
}
