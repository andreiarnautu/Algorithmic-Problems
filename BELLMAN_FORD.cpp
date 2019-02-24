/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <queue>
#include <bitset>
#define DIM 50500
#define INF 2000000000
#define PII pair<int,int>
#define fi first
#define se second
using namespace std;

FILE *fin=freopen("bellmanford.in","r",stdin);
FILE *fout=freopen("bellmanford.out","w",stdout);
vector < PII > M[DIM];
queue <int> Q;
bitset <DIM> ok;
int dmin[DIM], in[DIM];
int n, m;

void Read()
{
    int i, x, y, cost;
    scanf("%d %d", &n, &m);
    for(i = 1; i <= m; ++i)
    {
        scanf("%d %d %d", &x, &y, &cost);
        M[x].push_back( make_pair(y, cost) );
    }
    for(i = 2; i <= n; ++i)
        dmin[i] = INF;
}

void Write()
{
    for(int i = 2; i <= n; ++i)
        printf("%d ", dmin[i]);
}

void Solve()
{
    PII aux;
    int i, vf;

    Q.push( 1 ); ok[1] = 1; in[ 1 ] = 1;
    while( !Q.empty() )
    {
        vf = Q.front(); Q.pop(); ok[ vf ] = 0;
        for(i = 0; i < M[vf].size(); ++i)
        {
            aux = M[vf][i];
            if( dmin[ aux.fi ] > dmin[ vf ] + aux.se )
            {
                dmin[ aux.fi ] = dmin[ vf ] + aux.se;
                if( ok[ aux.fi ] == 0 )
                {
                    ok[ aux.fi ] = 1;
                    ++in[ aux.fi ];
                    Q.push( aux.fi );
                    if( in[ aux.fi ] >= n )
                    {
                        printf("Ciclu negativ!");
                        return;
                    }
                }
            }
        }
    }

    Write();
}

int main()
{
    Read();
    Solve();
}
