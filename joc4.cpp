/**
  *  Worg
  */
#include <queue>
#include <bitset>
#include <vector>
#include <fstream>
#include <algorithm>

#define pb      push_back
#define dim     510
#define in(i)   (i * 2)
#define out(i)  (i * 2 + 1)
#define inFile  "joc4.in"
#define outFile "joc4.out"

using namespace std;

queue  < short int > Q;
bitset < dim > v;
vector < short int > G[dim];
vector < short int >::iterator it;

char c[dim][dim], f[dim][dim];
short int father[dim];
short int n, m, source, sink, flow;

void read() {

    ifstream cin(inFile);
    cin >> n >> m >> source >> sink;

    for(int i = 1; i <= n; ++i) {

        G[in(i)].pb(out(i));
        G[out(i)].pb(in(i));

        c[in(i)][out(i)] = 2, f[in(i)][out(i)] = 1;
        c[out(i)][in(i)] = 1, f[out(i)][in(i)] = 1;
    }

    int x, y;
    for(int i = 1; i <= m; ++i) {

        cin >> x >> y;

        G[out(x)].pb(in(y));
        G[in(y)].pb(out(x));
        c[in(y)][out(x)] = 1, f[in(y)][out(x)] = 1;
        c[out(x)][in(y)] = 2, f[out(x)][in(y)] = 1;

        G[in(x)].pb(out(y));
        G[out(y)].pb(in(x));
        c[in(x)][out(y)] = 1, f[in(x)][out(y)] = 1;
        c[out(y)][in(x)] = 2, f[out(y)][in(x)] = 1;
    }

    c[in(source)][out(source)] = c[out(source)][in(source)] = c[in(sink)][out(sink)] = c[out(sink)][in(sink)] = 110;
}

void set() {

    while( !Q.empty() )
        Q.pop();
    for(int i = 1; i <= n * 2 + 2; ++i)
        v[i] = 0;
}

int BFS() {

    set();
    Q.push(in(source));

    int node;
    while( !Q.empty() ) {

        node = Q.front(); Q.pop();
        if(node == out(sink))
            return 1;

        for(it = G[node].begin(); it != G[node].end(); ++it)
            if(!v[*it] && c[node][*it] > f[node][*it]) {

                v[*it] = 1;
                father[*it] = node;
                Q.push(*it);
            }
    }

    return 0;
}

void solve() {

    int node, flowMin;

    for(; BFS();)
        for(it = G[out(sink)].begin(); it != G[out(sink)].end(); ++it) {

            node = *it;
            if(!v[*it] || c[*it][out(sink)] == f[*it][out(sink)])
                continue;

            father[out(sink)] = *it;
            flowMin = 1;

            for(node = out(sink); node != in(source); node = father[node])
                flowMin = min(flowMin, c[father[node]][node] - f[father[node]][node]);

            if(!flowMin)
                continue;
            ++flow;
            for(node = out(sink); node != in(source); node = father[node])
                ++f[father[node]][node],
                --f[node][father[node]];
        }
}

void write() {

    ofstream cout(outFile);
    cout << flow;
}

int main() {

    read();
    solve();
    write();
    return 0;
}
