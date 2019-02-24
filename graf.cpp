// How about a coding trick?
#include <cstdio>
#include <queue>
#include <vector>
#define DIM 7575
using namespace std;
FILE *fin=freopen("graf.in","r",stdin);
FILE *fout=freopen("graf.out","w",stdout);

vector <int> V[DIM], Levels[DIM * 2];
vector <int>::iterator it;
queue <int> Q;
int dmin[2][DIM], F[DIM];
int n, m, x, y;


void Read()
{
    int i, v1, v2;
    scanf("%d%d%d%d", &n, &m, &x, &y);
    for(i = 1; i <= m; ++i)
    {
        scanf("%d %d", &v1, &v2);
        V[v1].push_back( v2 );
        V[v2].push_back( v1 );
    }
}

void BFS(int nod, int k)
{
    int i, vf;
    for(i = 1; i <= n; ++i)
        dmin[k][i] = 0;
    dmin[k][nod] = 1;
    Q.push(nod);
    while( !Q.empty() )
    {
        vf = Q.front(); Q.pop();
        for(it = V[vf].begin(); it != V[vf].end(); ++it)
            if( !dmin[k][*it] )
            {
                dmin[k][*it] = dmin[k][vf] + 1;
                Q.push(*it);
            }
    }
}

int main()
{
    Read();
    BFS(x, 0);
    BFS(y, 1);
    int i, len = dmin[0][y], cnt = 0;
    for(i = 1; i <= n; ++i)
        if( dmin[0][i] && dmin[1][i] )
        {
            if( len == dmin[0][i] + dmin[1][i] - 1 )
                Levels[dmin[0][i] - 1].push_back(i);
        }
    for(i = 1; i <= len; ++i)
        if( Levels[i].size() == 1 )
            F[Levels[i][0]] = 1;
    F[x] = F[y] = 1;
    for(i = 1; i <= n; ++i)
        if( F[i] )
            ++cnt;
    printf("%d\n", cnt);
    for(i = 1; i <= n; ++i)
        if( F[i] )
            printf("%d ", i);
    return 0;
}
