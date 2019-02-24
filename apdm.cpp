/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

#define pb          push_back
#define INF         1000000000
#define MAX_N       1 + 150

using namespace std;
FILE *fin=freopen("apdm.in","r",stdin);
FILE *fout=freopen("apdm.out","w",stdout);

queue < int > Q;
vector < int > G[MAX_N], H[MAX_N];

int dist[MAX_N][MAX_N];
int dmin[MAX_N];
int n, m, sol = INF;

void readData() {

    scanf("%d %d ", &n, &m);

    int x, y;
    for(int i = 1; i <= m; ++i) {

        scanf("%d %d ", &x, &y);
        G[x].pb(y);
        G[y].pb(x);
    }
}

void getTree(int node) {

    dmin[node] = 0;
    Q.push(node);

    while(!Q.empty()) {

        node = Q.front(); Q.pop();
        for(vector <int>::iterator it = G[node].begin(); it != G[node].end(); ++it)
            if(dmin[*it] == INF) {

                dmin[*it] = dmin[node] + 1;
                H[node].pb(*it); H[*it].pb(node);
                Q.push(*it);
            }
    }
}

void getDiameter() {

    int dist = -1, start, node;
    for(int i = 1; i <= n; ++i)
        if(dist < dmin[i])
            dist = dmin[i], start = i;

    for(int i = 1; i <= n; ++i)
        dmin[i] = INF;
    dmin[start] = 0;
    Q.push(start);

    while(!Q.empty()) {

        node = Q.front(); Q.pop();
        for(vector < int >::iterator it = H[node].begin(); it != H[node].end(); ++it)
            if(dmin[*it] == INF) {

                dmin[*it] = dmin[node] + 1;
                Q.push(*it);
            }
    }
    int dmax = 0;
    for(int i = 1; i <= n; ++i)
        dmax = max(dmax, dmin[i]);
    sol = min(sol, dmax);
}

void resetTree() {

    for(int i = 1; i <= n; ++i) {

        dmin[i] = INF;
        H[i].clear();
    }
}

int main() {

    readData();
    for(int i = 1; i <= n; ++i) {

        resetTree();
        getTree(i);
        for(int j = 1; j <= n; ++j)
            dist[i][j] = dmin[j];
        getDiameter();
        for(vector <int>::iterator it = G[i].begin(); it != G[i].end(); ++it)
            if(i > *it) {

                int d1 = 0, d2 = 0, d3 = 0, d4 = 0, partial;
                for(int j = 1; j <= n; ++j)
                    if(j != i && j != *it) {

                        if(dist[i][j] <= dist[*it][j]) {

                            if(d1 < dist[i][j])
                                d2 = d1, d1 = dist[i][j];
                            else if(d2 < dist[i][j])
                                d2 = dist[i][j];
                        }
                        else {

                            if(d3 < dist[*it][j])
                                d4 = d3, d3 = dist[*it][j];
                            else if(d4 < dist[*it][j])
                                d4 = dist[*it][j];
                        }

                    }
                partial = max(d1 + d3 + 1, 1 + max(d1 + d2, d3 + d4));
                sol = min(sol, partial);
            }
    }
    printf("%d", sol);
    return 0;
}
