/**
  *  Worg
  */
#include <queue>
#include <stack>
#include <cstdio>
#include <vector>

#define pb          push_back

using namespace std;
FILE *fin = freopen("cartite.in", "r", stdin);
FILE *fout = freopen("cartite.out", "w", stdout);

const int MAX_N = 1 + 200,
          MAX_K = 1 + 50,
          MAX_G = 1 + 100;

struct edge {

    int index, vertex;
    edge(const int index, const int vertex) {

        this->index = index; this->vertex = vertex;
    }
};

struct point {

    int x, y;
    point(const int x, const int y) {

        this->x = x; this->y = y;
    }
};

struct fox {

    int x, y, type;
    fox(const int x, const int y, const int type) {

        this->x = x; this->y = y; this->type = type;
    }
};

stack < int > stiva;
queue < point > coada;
vector < edge > G[MAX_G];
vector < point > type[3], dir, casuta, sol;
vector < fox > F;

bool inRange[MAX_N][MAX_N], checked[MAX_N][MAX_N], parcurs[MAX_G];

int val[MAX_N][MAX_N], dist[MAX_N][MAX_N];
int degree[MAX_G];
int p, m, n, x0, y0, k, g;
int N, M;

void generateFoxTypes() {
    /* type 0 */
    type[0].pb(point(0, 0));
    /* type 1 */
    type[1].pb(point(0, 0)); type[1].pb(point(-1, 0)); type[1].pb(point(1, 0)); type[1].pb(point(0, -1)); type[1].pb(point(0, 1));
    /* type 2 */
    type[2].pb(point(0, 0)); type[2].pb(point(-1, 0)); type[2].pb(point(1, 0)); type[2].pb(point(0, -1)); type[2].pb(point(0, 1));
    type[2].pb(point(-1,-1)); type[2].pb(point(-1, 1)); type[2].pb(point(1, -1)); type[2].pb(point(1, 1));
    type[2].pb(point(-2, 0)); type[2].pb(point(2, 0)); type[2].pb(point(0, -2)); type[2].pb(point(0, 2));
}

void addEdge(const int u, const int v) {

    G[u].pb(edge(M, v));
    G[v].pb(edge(M, u));
    degree[u]++, degree[v]++;
    M++;
}

int deleteNext(int node) {

    while(!G[node].empty() && parcurs[G[node].back().index])
        G[node].pop_back();
    if(!G[node].empty()) {

        int nxt = G[node].back().vertex;
        parcurs[G[node].back().index] = true;
        G[node].pop_back();

        degree[node]--, degree[nxt]--;
        M--;
        return nxt;
    }
    return 0;
}

void readData() {

    scanf("%d %d %d ", &p, &m, &n);
    scanf("%d %d ", &x0, &y0);
    scanf("%d ", &k);
    for(int i = 1; i <= k; ++i) {

        int x, y, type; scanf("%d %d %d ", &x, &y, &type);
        F.pb(fox(x, y, type));
    }
    scanf("%d ", &g);
    casuta.pb(point(0, 0));
    for(int i = 1; i <= g; ++i) {

        int x1, y1, x2, y2; scanf("%d %d %d %d ", &x1, &y1, &x2, &y2);
        if(!val[x1][y1]) {

            val[x1][y1] = ++N;
            casuta.pb(point(x1, y1));
        }
        if(!val[x2][y2]) {

            val[x2][y2] = ++N;
            casuta.pb(point(x2, y2));
        }
        addEdge(val[x1][y1], val[x2][y2]);
    }
}

bool validCell(const int x, const int y) {

    return (x && y && x <= m && y <= n);
}

void setMatrix() {

    for(vector < fox >::iterator it = F.begin(); it != F.end(); ++it)
        for(vector < point >::iterator i = type[it->type].begin(); i != type[it->type].end(); ++i) {

            int x = it->x + i->x, y = it->y + i->y;
            if(validCell(x, y))
                inRange[x][y] = true;
        }
}

void bellmanFord() {

    dir.pb(point(-1, 0)); dir.pb(point(1, 0)); dir.pb(point(0, -1)); dir.pb(point(0, 1));
    coada.push(point(x0, y0));
    checked[x0][y0] = true;

    while(!coada.empty()) {

        int x = coada.front().x, y = coada.front().y; coada.pop();
        if(val[x][y]) { /* daca se gaseste o intrare pe pozitia curenta */

            printf("%d %d %d\n", x, y, dist[x][y]);
            return;
        }
        for(vector < point >::iterator it = dir.begin(); it != dir.end(); ++it) {

            int X = x + it->x, Y = y + it->y;
            if(validCell(X, Y) && !checked[X][Y] && !inRange[X][Y]) {

                dist[X][Y] = dist[x][y] + 1;
                checked[X][Y] = 1;
                coada.push(point(X, Y));
            }
        }
    }
}

void eulerianCycle() {

    int i;
    for(i = 1; inRange[casuta[i].x][casuta[i].y]; ++i);
    stiva.push(i);
    while(!stiva.empty()) {

        int node = stiva.top();
        if(degree[node])
            stiva.push(deleteNext(node));
        else {

            sol.pb(casuta[node]);
            stiva.pop();
        }
    }
    for(vector < point >::iterator it = sol.begin(); it != sol.end(); ++it)
        printf("%d %d\n", it->x, it->y);
}

int main() {

    generateFoxTypes();
    readData();
    setMatrix();
    if(p == 1)
        bellmanFord();
    else
        eulerianCycle();
    return 0;
}
