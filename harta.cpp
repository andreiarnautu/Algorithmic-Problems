/**
  *  Worg
  */
#include <queue>
#include <vector>
#include <fstream>
#include <algorithm>

#define dim     250
#define pb      push_back
#define mp      make_pair
#define in(i)   i
#define out(i)  n + i
#define sink    (2 * n + 1)
#define source  0
#define inFile  "harta.in"
#define outFile "harta.out"

using namespace std;

queue  < int > Q;
vector < int > G[dim];
vector < int >::iterator it;

int c[dim][dim], f[dim][dim];
int father[dim];
int n;

void read() {

    int x, y;

    ifstream cin(inFile);
    cin >> n;
    for(int i = 1; i <= n; ++i) {

        cin >> x >> y;
        G[source].pb(in(i));
        G[in(i)].pb(source);
        c[source][in(i)] = x;

        G[out(i)].pb(sink);
        G[sink].pb(out(i));
        c[out(i)][sink] = y;
    }
}

void build() {

    for(int i = 1; i < n; ++i)
        for(int j = i + 1; j <= n; ++j) {

            G[in(i)].pb(out(j));
            G[out(j)].pb(in(i));
            c[in(i)][out(j)] = 1;

            G[in(j)].pb(out(i));
            G[out(i)].pb(in(j));
            c[in(j)][out(i)] = 1;
        }
}

int BFS() {

    for(int i = 1; i <= sink; ++i)
        father[i] = -1;
    while( !Q.empty() )
        Q.pop();

    int node;
    Q.push(source);
    while( !Q.empty() ) {

        node = Q.front(); Q.pop();
        if(node == sink)
            return 1;
        for(it = G[node].begin(); it != G[node].end(); ++it)
            if(father[*it] == -1 && c[node][*it] > f[node][*it]) {

                father[*it] = node;
                Q.push(*it);
            }
    }

    return 0;
}

void write() {

    ofstream cout(outFile);

    int ans = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            if(i != j && f[in(i)][out(j)] == c[in(i)][out(j)])
                ++ans;

    cout << ans << '\n';
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            if(i != j && f[in(i)][out(j)] == c[in(i)][out(j)])
                cout << i << " " << j << '\n';
}

int main() {

    read();
    build();

    int node, flowMin;
    while( BFS() ) {

        for(it = G[sink].begin(); it != G[sink].end(); ++it) {

            if(c[*it][sink] == f[*it][sink] || father[*it] == -1)
                continue;

            father[sink] = *it;
            flowMin = 1000;
            for(int i = sink; i != source; i = father[i])
                flowMin = min(flowMin, c[father[i]][i] - f[father[i]][i]);

            if(!flowMin)
                continue;

            for(int i = sink; i != source; i = father[i])
                f[father[i]][i] += flowMin,
                f[i][father[i]] -= flowMin;
        }
    }

    write();
    return 0;
}
