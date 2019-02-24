/**
  *  Worg
  */
#include <cmath>
#include <deque>
#include <bitset>
#include <vector>
#include <fstream>
#include <algorithm>

#define dim 1010
#define inf 1000000000
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define inFile "critice.in"
#define outFile "critice.out"

using namespace std;

int N;
vector < int > G[dim], ans;
vector < pair<int,int> > M;
bitset < dim > v;
deque  < int > Q;
vector < int >::iterator it;
vector < pair<int,int> >::iterator it2;

int c[dim][dim], f[dim][dim], E[dim];
int father[dim];
int n, m, flow;

void read() {

    int x, y, z;
    ifstream cin(inFile);
    cin >> n >> m;

    for(int i = 1; i <= m; ++i) {

        cin >> x >> y >> z;
        c[x][y] += z, c[y][x] += z;
        G[x].pb(y); G[y].pb(x);
        M.pb(mp(x, y));
    }
}

int BFS() {

    int node, son;
    for(int i = 2; i <= n; ++i)
        v[i] = 0;
    v[1] = 1;

    Q.clear(); Q.pb(1);
    while( !Q.empty() ) {

        node = Q.front(); Q.pop_front();
        if(node == n)
            continue;

        for(it = G[node].begin(); it != G[node].end(); ++it) {

            son = *it;
            if(v[son] || c[node][son] == f[node][son])
                continue;
            v[son] = 1;
            Q.pb(son);
            father[son] = node;
        }
    }
    return v[n];
}

void getFlow() {

    int node, flowMin;
    for(; BFS();)
        for(it = G[n].begin(); it != G[n].end(); ++it) {

            node = *it;
            if(!v[node] || c[node][n] == f[node][n])
                continue;

            father[n] = node;
            flowMin = inf;
            for(node = n; node > 1; node = father[node])
                flowMin = min(flowMin, c[father[node]][node] - f[father[node]][node]);

            if(!flowMin)
                continue;

            flow += flowMin;
            for(node = n; node > 1; node = father[node])
                    f[father[node]][node] += flowMin,
                    f[node][father[node]] -= flowMin;
            }
}

void DFS(int start, int k) {

    E[start] = k;
    for(vector <int>::iterator x = G[start].begin(); x != G[start].end(); ++x)
        if( !E[*x] && f[start][*x] < c[start][*x] )
            DFS(*x, k);
}

void findEdges() {

    int a, b, i;
    for(it2 = M.begin(), i = 1; it2 != M.end(); ++it2, ++i) {

        a = it2->fi, b = it2->se;
        if(c[a][b] == abs(f[a][b]) && E[a] + E[b] == 3)
            ans.pb(i);
    }
}

void write() {

    ofstream cout(outFile);
    cout << ans.size() << '\n';
    for(it = ans.begin(); it != ans.end(); ++it)
        cout << *it << '\n';
}

int main() {

    read();
    getFlow();
    DFS(1, 1);
    DFS(n, 2);
    findEdges();
    write();
    return 0;
}
