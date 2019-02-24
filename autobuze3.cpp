/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

#define pb          push_back

using namespace std;
FILE *fin = freopen("autobuze3.in", "r", stdin);
FILE *fout = freopen("autobuze3.out", "w", stdout);

const int bufferDim = 10000,
          MAX_N = 1 + 100000;

class inputReader {

private:
        char buffer[bufferDim];
        int pos;
public:
        void getBuffer() {

            fread(buffer, 1, bufferDim, stdin);
            pos = 0;
        }

        bool digit(const char &c) {

            return ('0' <= c && c <= '9');
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

    bool operator <(const edge &other) const{

        return this->cost < other.cost;
    }
};

vector < edge > candidates;
vector < neighbour > A[MAX_N];
vector < int > drivers[MAX_N];

bool checked[MAX_N];
int father[MAX_N], bus[MAX_N];
int m, n;

int group(int x) {

    if(x != father[x])
        father[x] = group(father[x]);
    return father[x];
}

void unite(int x, int y) {

    father[x] = y;
}

void readData() {

    candidates.clear();
    for(int i = 1; i <= n; ++i)
        A[i].clear();

    cin.getInt(n); cin.getInt(m);

    for(int i = 1; i <= m; ++i) {

        int x, y, c;
        cin.getInt(x); cin.getInt(y); cin.getInt(c);
        candidates.pb(edge(x, y, c));
    }
}

void getAPM() {

    sort(candidates.begin(), candidates.end());
    int needed = n - 1, cost = 0;

    for(int i = 1; i <= n; ++i)
        father[i] = i;

    for(int i = 0; needed && i < candidates.size(); ++i) {

        int x = candidates[i].a, y = candidates[i].b;
        int rx = group(x), ry = group(y);

        if(rx != ry) {

            A[x].pb(neighbour(y, candidates[i].cost));
            A[y].pb(neighbour(x, candidates[i].cost));
            unite(rx, ry);
            --needed;
            cost += candidates[i].cost;
        }
    }
    printf("%d\n", cost);
}

void setDrivers() {

    for(int i = 1; i <= n; ++i) {

        drivers[i].clear();
        drivers[i].pb(i);
        checked[i] = false;
        bus[i] = i;
    }
}

void dfs(int node) {

    checked[node] = true;
    for(vector < neighbour >::iterator it = A[node].begin(); it != A[node].end(); ++it)
        if(!checked[it->vertex]) {

            dfs(it->vertex);
            printf("Drive %d %d %d\n", bus[it->vertex], it->vertex, node);

            if(drivers[bus[node]].size() >= drivers[bus[it->vertex]].size()) {

                for(int i = drivers[bus[it->vertex]].size() - 1; i >= 0; --i) {

                    drivers[bus[node]].pb(drivers[bus[it->vertex]][i]);
                    printf("Move %d %d %d\n", drivers[bus[it->vertex]][i], bus[it->vertex], bus[node]);
                    drivers[bus[it->vertex]].pop_back();
                }
            }
            else {

                for(int i = drivers[bus[node]].size() - 1; i >= 0; --i) {

                    drivers[bus[it->vertex]].pb(drivers[bus[node]][i]);
                    printf("Move %d %d %d\n", drivers[bus[node]][i], bus[node], bus[it->vertex]);
                    drivers[bus[node]].pop_back();
                }
                bus[node] = bus[it->vertex];
            }
        }
}

int main() {

    cin.getBuffer();
    int t;
    for(cin.getInt(t); t; --t) {

        readData();
        getAPM();
        setDrivers();
        dfs(1);
        printf("Gata\n");
    }
    return 0;
}
