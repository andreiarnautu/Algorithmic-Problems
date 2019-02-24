/**
  *  Worg
  *  Max-Flow
  */
#include <deque>
#include <bitset>
#include <vector>
#include <fstream>
#include <algorithm>

#define dim 1010
#define inf 1000000000
#define pb push_back
#define pf push_front
#define inFile "maxflow.in"
#define outFile "maxflow.out"

using namespace std;

vector < int > G[dim];
deque  < int > Q;
bitset < dim > v;
vector < int >::iterator it;
int c[dim][dim], f[dim][dim];
int father[dim];
int m, n;

int BFS() {

    int node, son;

    for(int i = 2; i <= n; ++i)
        v[i] = 0;
    v[1] = 1;
    Q.clear(); Q.pb(1);

    while( !Q.empty() ) {

        node = Q.front(); Q.pop_front();
        if( node == n )
            return 1;

        for(it = G[node].begin(); it != G[node].end(); ++it) {

            son = *it;
            if( v[son] || c[node][son] == f[node][son] )
                continue;
            v[son] = 1;
            Q.pb(son);
            father[son] = node;
        }
    }

    return 0;
}

int main() {

    ifstream cin(inFile);
    ofstream cout(outFile);

    int flow = 0, flowMin, x, y, z, node;

    cin >> n >> m;
    for(int i = 1; i <= m; ++i) {

        cin >> x >> y >> z;
        c[x][y] += z;
        G[x].pb(y);
        G[y].pb(x);
    }

    for(; BFS();)
        for(it = G[n].begin(); it != G[n].end(); ++it) {

            node = *it;
            if(c[node][n] == f[node][n] || !v[node])
                continue;

            father[n] = node;
            flowMin = inf;
            for(node = n; node > 1; node = father[node])
                flowMin = min(flowMin, c[father[node]][node] - f[father[node]][node] );

            if( !flowMin )
                continue;

            flow += flowMin;
            for(node = n; node > 1; node = father[node])
                f[father[node]][node] += flowMin,
                f[node][father[node]] -= flowMin;
        }

    cout << flow;
    return 0;
}
