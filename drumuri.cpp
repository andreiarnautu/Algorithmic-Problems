/**
  *  Worg
  */
#include <queue>
#include <bitset>
#include <vector>
#include <fstream>

#define dim 220
#define in(i)   (i * 2)
#define out(i)  (i * 2 + 1)
#define source  (n * 2 + 2)
#define sink    (n * 2 + 3)
#define inFile  "drumuri.in"
#define outFile "drumuri.out"
#define pb      push_back

using namespace std;

int c[dim][dim], f[dim][dim];
int nxt[dim];
int n, m, flow;
bitset < dim > v;
queue  < int > Q;
vector < int > G[dim];
vector < int >::iterator it;

void read() {

    int x, y;
    ifstream cin(inFile);
    cin >> n >> m;

    for(int i = 1; i <= m; ++i) {

        cin >> x >> y;
        c[out(x)][in(y)] = n;
        G[out(x)].pb(in(y));
        G[in(y)].pb(out(x));
    }

    for(int i = 1; i <= n; ++i) {

        G[source].pb(in(i));
        G[in(i)].pb(source);

        G[in(i)].pb(out(i));
        G[out(i)].pb(in(i));

        G[out(i)].pb(sink);
        G[sink].pb(out(i));

        c[in(i)][out(i)] = n;
        c[source][in(i)] = n, f[source][in(i)] = 1, f[in(i)][source] = -1;
        c[out(i)][sink]  = n, f[out(i)][sink]  = 1, f[sink][out(i)]  = -1;
    }
}

int BFS() {

    int node;
    for(int i = 1; i <= sink; ++i)
        v[i] = 0;

    while( !Q.empty() )
         Q.pop();

    Q.push(sink); v[sink] = 1;
    while( !Q.empty() ) {

        node = Q.front(); Q.pop();
        for(it = G[node].begin(); it != G[node].end(); ++it)
            if(!v[*it] && c[node][*it] > f[node][*it]) {

                Q.push(*it);
                nxt[*it] = node;
                v[*it] = 1;
            }
    }

    if( !v[source] )
        return 0;

    for(int i = source; i != sink; i = nxt[i])
        --f[i][nxt[i]],
        ++f[nxt[i]][i];

    return 1;
}

void getFlow() {

    for(flow = n; BFS() && flow; --flow);
}

void write() {

    ofstream cout(outFile);
    cout << flow;
}

int main() {

    read();
    getFlow();
    write();
}
