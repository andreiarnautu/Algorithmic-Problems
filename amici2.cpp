/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

#define pb          push_back
#define MAX_N       1 + 21000

using namespace std;
FILE *fin=freopen("amici2.in","r",stdin);
FILE *fout=freopen("amici2.out","w",stdout);

queue <int> Q;
vector <int> G[MAX_N];

int dmin[MAX_N];
int n, m, dist;

void bfs(int start) {

    for(int i = 1; i <= n; ++i)
        dmin[i] = 1000000;
    dmin[start] = dist = 0;
    Q.push(start);

    while(!Q.empty()) {

        int node = Q.front(); Q.pop();

        for(vector <int>::iterator it = G[node].begin(); it != G[node].end(); ++it)
            if(dmin[*it] == 1000000) {

                dmin[*it] = dmin[node] + 1;
                dist = max(dist, dmin[*it]);
                Q.push(*it);
            }
    }
}

int main() {

    int t, sol;
    for(scanf("%d ", &t); t; --t) {

        scanf("%d %d ", &n, &m);
        for(int i = 1; i <= n; ++i)
            G[i].clear();
        for(int i = 1; i <= m; ++i) {

            int x, y;
            scanf("%d %d ", &x, &y);
            G[x].pb(y); G[y].pb(x);
        }
        bfs(1);
        for(sol = 0; (1 << sol) < dist; ++sol);
        printf("%d\n", sol);
    }
    return 0;
}
