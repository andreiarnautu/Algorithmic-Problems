/**
  *  I am Worg.
  *  Descriere solutie:
  *     a)  Se face DFS din nodul 1, parcurgand doar muchiile cu cost <= D[1].
  *         Dintre nodurile vizitate, se alege cel care are D[nod] maxim.
  *     b)  Nodurile sunt de forma (insula, dragon).
  *         Se foloseste BF pornind din nodul (1, 1).
  */

#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

#define fi          first
#define se          second
#define mp          make_pair
#define pb          push_back
#define INF         1LL * 1000000000 * 1000000000
#define MAX_N       1 + 800

using namespace std;
FILE *fin=freopen("dragoni.in","r",stdin);
FILE *fout=freopen("dragoni.out","w",stdout);

queue  < pair<int, int> > Q;
vector < pair<long long int, int> > G[MAX_N];
vector < pair<long long int, int> >::iterator it;

bool inQueue[MAX_N][MAX_N], ok[MAX_N][MAX_N];
bool viz[MAX_N];
long long int dmin[MAX_N][MAX_N];
long long int D[MAX_N];
int m, n, p;

void readData() {

    scanf("%d %d %d ", &p, &n, &m);
    for(int i = 1; i <= n; ++i)
        scanf("%lld ", &D[i]);
    int x, y;
    long long int z;
    for(int i = 1; i <= m; ++i) {

        scanf("%d %d %lld ", &x, &y, &z);
        G[x].pb(mp(z, y));
        G[y].pb(mp(z, x));
    }

    for(int i = 1; i <= n; ++i)
        sort(G[i].begin(), G[i].end());
}

void dfs(int node) {

    viz[node] = 1;
    for(vector< pair<long long int, int> >::iterator i = G[node].begin(); i != G[node].end(); ++i) {
        if(!viz[i->se] && i->fi <= D[1])
            dfs(i->se);
        else if(i->fi > D[1])
            break;
    }
}

void task_1() {

    dfs(1);
    long long int sol = D[1];
    for(int i = 1; i <= n; ++i)
        if(viz[i])
            sol = max(sol, D[i]);
    printf("%lld\n", sol);
}

void initialize() {

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            dmin[i][j] = INF;
    dmin[1][1] = 0;
}

void task_2() {

    long long int sol = INF, island, dist;
    int dragon;
    initialize();

    Q.push(mp(1, 1));
    while(!Q.empty()) {

       island = Q.front().fi, dragon = Q.front().se; Q.pop();
       inQueue[island][dragon] = 0;
       dist = dmin[island][dragon];

       if(D[island] > D[dragon])
            dragon = island;
       for(it = G[island].begin(); it != G[island].end() && it->fi <= D[dragon]; ++it)
            if(dist + it->fi <= sol && dist + it->fi <= dmin[it->se][dragon]) {

                if(it->se == n)
                    sol = dist + it->fi;

                else {

                    dmin[it->se][dragon] = dist + it->fi;
                    if(!inQueue[it->se][dragon]) {

                        Q.push(mp(it->se, dragon));
                        inQueue[it->se][dragon] = 1;
                    }
                }
            }
    }

    printf("%lld\n", sol);
}

int main() {

    readData();
    if(p == 1)
        task_1();
    else
        task_2();
    return 0;
}
