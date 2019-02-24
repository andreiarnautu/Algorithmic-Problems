// How about a coding trick?
#include <cstdio>
#include <vector>
#include <algorithm>
#define DIM 80000
#define INF 2000000000
#define PII pair<int,int>
#define fi first
#define se second

using namespace std;
FILE *fin=freopen("catun.in","r",stdin);
FILE *fout=freopen("catun.out","w",stdout);

int heap[DIM], pos[DIM], previous[DIM], dmin[DIM];
vector < PII > V[DIM];
int n, m, k, nr;

inline int father(int nod)
{
    return nod / 2;
}

inline int left_son(int nod)
{
    return nod * 2;
}

inline int right_son(int nod)
{
    return nod * 2 + 1;
}


inline int up(int nod)
{
    int key = heap[nod];

    while( nod > 1 && dmin[key] < dmin[ heap[father(nod)] ] )
    {
        heap[nod] = heap[ father(nod) ];
        pos[ heap[nod] ] = nod;
        nod = father(nod);
    }
    heap[nod] = key;
    return nod;
}

inline int down(int nod)
{
    int son = 1;
    while( son )
    {
        son = 0;
        if( left_son(nod) <= nr )
        {
            son = left_son(nod);
            if( right_son(nod) <= nr && dmin[heap[right_son(nod)]] < dmin[heap[left_son(nod)]] )
                son = right_son(nod);

            if( dmin[heap[son]] > dmin[heap[nod]] )
                son = 0;
        }
        if( son )
        {
            swap( heap[son], heap[nod] );
            pos[ heap[nod] ] = nod;
            nod = son;
        }
    }
    return nod;
}

inline void Add(int nod)
{
    heap[++nr] = nod;
    pos[nod] = up(nr);
}

inline void pop()
{
    heap[1] = heap[nr], --nr;
    pos[ heap[1] ] = down( 1 );
}

void Read()
{
    int i, x, y, cost;
    scanf("%d %d %d", &n, &m, &k);
    for(i = 1; i <= n; ++i)
        dmin[i] = INF;
    for(i = 1; i <= k; ++i)
    {
        scanf("%d", &x);
        dmin[x] = 0; previous[x] = x;
        Add(x);
    }
    for(i = 1; i <= m; ++i)
    {
        scanf("%d %d %d", &x, &y, &cost);
        V[x].push_back( make_pair(y, cost) );
        V[y].push_back( make_pair(x, cost) );
    }
}

void Solve()
{
    int vf, i;

    while( nr )
    {
        vf = heap[1]; pop(); pos[vf] = 0;

        for(i = 0; i < V[vf].size(); ++i)
            if( dmin[ V[vf][i].fi ] > dmin[vf] + V[vf][i].se  || ( dmin[ V[vf][i].fi ] == dmin[vf] + V[vf][i].se && previous[ V[vf][i].fi ] > previous[ vf ] ) )
            {
                previous[ V[vf][i].fi ] = previous[ vf ];
                dmin[ V[vf][i].fi ] = dmin[vf] + V[vf][i].se;

                if( !pos[ V[vf][i].fi ] )
                    Add( V[vf][i].fi );
                else
                    pos[ V[vf][i].fi ] = up( pos[ V[vf][i].fi ] );
            }
    }
}

void Write()
{
    int i;
    for(i = 1; i <= n; ++i)
    {
        if( dmin[i] == INF || dmin[i] == 0 )
            printf("0 ");
        else
            printf("%d ", previous[i]);
    }
}

int main()
{
    Read();
    Solve();
    Write();
    return 0;
}
