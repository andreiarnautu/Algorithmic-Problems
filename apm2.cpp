/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

#define pb      push_back

using namespace std;
FILE *fin = freopen("apm2.in", "r", stdin);
FILE *fout = freopen("apm2.out", "w", stdout);

const int MAX_N = 1 + 10000, bufferDim = 10000;

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

struct neighbour {

    int vertex, cost;

    neighbour(const int &vertex, const int &cost) {

        this->vertex = vertex, this->cost = cost;
    }
};

struct edge {

    int a, b, cost;

    edge(const int &a, const int &b, const int &cost) {

        this->a = a, this->b = b, this->cost = cost;
    }

    bool operator <(const edge &other) const {

        return this->cost > other.cost;
    }
};

priority_queue < edge > candidates;
vector < neighbour > G[MAX_N], A[MAX_N];

bool viz[MAX_N], solved[MAX_N];
int maxEdge[MAX_N];
int n, m, q;

void readData() {

    cin.getInt(n);
    cin.getInt(m);
    cin.getInt(q);

    for(int i = 1; i <= m; ++i) {

        int a, b, cost;
        cin.getInt(a), cin.getInt(b), cin.getInt(cost);
        G[a].pb(neighbour(b, cost));
        G[b].pb(neighbour(a, cost));
    }
}

void getAPM() {

    solved[1] = true;
    for(vector < neighbour >::iterator it = G[1].begin(); it != G[1].end(); ++it)
        candidates.push(edge(1, it->vertex, it->cost));

    while(!candidates.empty()) {

        edge Edge = candidates.top(); candidates.pop();

        if(!(solved[Edge.a] && solved[Edge.b])) {

            A[Edge.a].pb(neighbour(Edge.b, Edge.cost));
            A[Edge.b].pb(neighbour(Edge.a, Edge.cost));

            int newNode = (solved[Edge.a] == true) ? Edge.b : Edge.a;
            for(vector < neighbour >::iterator it = G[newNode].begin(); it != G[newNode].end(); ++it)
                if(!solved[it->vertex])
                    candidates.push(edge(newNode, it->vertex, it->cost));
            solved[newNode] = true;
        }
    }
}

void dfs(int node) {

    viz[node] = true;
    for(vector < neighbour >::iterator it = A[node].begin(); it != A[node].end(); ++it)
        if(!viz[it->vertex]) {

            maxEdge[it->vertex] = max(maxEdge[node], it->cost);
            dfs(it->vertex);
        }
}

int main() {

    cin.getBuffer();
    readData();
    getAPM();

    for(int i = 1; i <= q; ++i) {

        int a, b;
        cin.getInt(a); cin.getInt(b);
        for(int j = 1; j <= n; ++j)
            maxEdge[j] = viz[j] = false;
        dfs(a);
        printf("%d\n", maxEdge[b] - 1);
    }
    return 0;
}
