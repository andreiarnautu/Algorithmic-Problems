/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>

#define pb      push_back

using namespace std;
FILE *fin = freopen("apm.in", "r", stdin);
FILE *fout = freopen("apm.out", "w", stdout);

const int MAX_N = 1 + 200000,
          MAX_M = 1 + 400000,
          bufferDim = 50000;

struct neighbour {

    int vertex, cost;

    neighbour(int vertex, int cost) {

        this->vertex = vertex;
        this->cost = cost;
    }
};

struct edge {

    int a, b, cost;

    edge(int a, int b, int cost) {

        this->a = a;
        this->b = b;
        this->cost = cost;
    }

    bool operator <(const edge &other) const {

        return this->cost > other.cost;
    }
};

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

        int getInt() {

            int ret = 0;
            char sign = '+';
            while(!digit(buffer[pos])) {

                sign = buffer[pos];
                if(++pos == bufferDim)
                    getBuffer();
            }
            while(digit(buffer[pos])) {

                ret = ret * 10 + buffer[pos] - '0';
                if(++pos == bufferDim)
                    getBuffer();
            }
            ret = (sign == '-') ? -ret : ret;
            return ret;
        }
};

priority_queue < edge > candidates;
vector < neighbour > G[MAX_N];
vector < edge > sol;
bool solved[MAX_N];

int m, n, solCost;

void readData() {

    inputReader cin;
    cin.getBuffer();
    n = cin.getInt(); m = cin.getInt();

    for(int i = 1; i <= m; ++i) {

        int x = cin.getInt(), y = cin.getInt(), cost = cin.getInt();
        G[x].pb(neighbour(y, cost));
        G[y].pb(neighbour(x, cost));
    }
}

void init() {

    solved[1] = true;

    for(vector < neighbour >::iterator it = G[1].begin(); it != G[1].end(); ++it)
        candidates.push(edge(1, it->vertex, it->cost));
}

void solve() {

    while(!candidates.empty()) {

        edge Edge = candidates.top();
        candidates.pop();

        if(!(solved[Edge.a] && solved[Edge.b])) {

            sol.pb(Edge);
            solCost += Edge.cost;

            int newNode = (solved[Edge.a] == true) ? Edge.b : Edge.a;
            for(vector < neighbour >::iterator it = G[newNode].begin(); it != G[newNode].end(); ++it)
                if(!solved[it->vertex])
                    candidates.push(edge(newNode, it->vertex, it->cost));
            solved[newNode] = true;
        }
    }
}

void writeData() {

    printf("%d\n%d\n", solCost, sol.size());
    for(vector < edge >::iterator it = sol.begin(); it != sol.end(); ++it)
        printf("%d %d\n", it->a, it->b);
}

int main() {

    readData();
    init();
    solve();
    writeData();
    return 0;
}
