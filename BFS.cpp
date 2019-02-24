// How about a coding trick?
#include <cstdio>
#include <vector>
#include <queue>
#define PII pair<int,int>
#define fi first
#define se second
#define DIM 100100
using namespace std;
FILE *fin=freopen("bfs.in","r",stdin);
FILE *fout=freopen("bfs.out","w",stdout);

vector <int> V[DIM];
vector <int>::iterator it;
queue < PII > Q;
int n, m, s;
int dist[DIM];

void Read()
{
    int i, x, y;
    scanf("%d%d%d", &n, &m, &s);
    for(i = 1; i <= m; ++i)
    {
        scanf("%d %d", &x, &y);
        V[x].push_back(y);
    }
}

void Solve()
{
    int i;
    PII vf;
    for(i = 1; i <= n; ++i)
        dist[i] = 0;
    dist[s] = 1;
    Q.push(make_pair(s, 1));
    while( !Q.empty() )
    {
        vf = Q.front(); Q.pop();
        for(it = V[vf.fi].begin(); it != V[vf.fi].end(); ++it)
            if( !dist[*it] )
            {
                dist[*it] = vf.se + 1;
                Q.push( make_pair(*it, vf.se + 1) );
            }
    }
    for(i = 1; i <= n; ++i)
    {
        if( !dist[i] )
            printf("-1 ");
        else
            printf("%d ", dist[i] - 1);
    }
}

int main()
{
    Read();
    Solve();
    return 0;
}
