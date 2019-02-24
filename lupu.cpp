// How about a coding trick?
#include <cstdio>
#include <algorithm>
#define DIM 1000100
using namespace std;
FILE *fin=freopen("lupu.in","r",stdin);
FILE *fout=freopen("lupu.out","w",stdout);

struct type{
                int T, lana;
           };

int Heap[DIM];
type V[DIM];
int nr, n, x, l;
long long int sol;

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

inline void up(int nod)
{
    int key = Heap[nod];

    while( nod > 1 && (Heap[father(nod)] < key) )
    {
        Heap[nod] = Heap[father(nod)];
        nod = father(nod);
    }

    Heap[nod] = key;
}

inline void down(int nod)
{
    int son = 1;

    while( son )
    {
        son = 0;
        if( left_son(nod) <= nr )
        {
            son = left_son(nod);
            if( right_son(nod) <= nr && Heap[right_son(nod)] > Heap[left_son(nod)] )
                son = right_son(nod);

            if( Heap[son] < Heap[nod] )
                son = 0;
        }

        if( son )
        {
            swap( Heap[nod], Heap[son] );
            nod = son;
        }
    }
}

inline bool comp(type a, type b)
{
    return a.T < b.T;
}

void Read()
{
    int i, d, a;
    scanf("%d%d%d", &n, &x, &l);

    if( !l )
    {
        for(int i = 1; i <= n; ++i)
        {
            scanf("%d%d", &d, &a);
            if( d <= x )
                sol += 1LL * a;
        }
        return;
    }

    for(i = 1; i <= n; ++i)
    {
        scanf("%d%d", &d, &a);
        V[i].T = (x - d) / l;
        V[i].lana = a;
        if( d > x )
            --i, --n;
    }

    sort(V + 1, V + n + 1, comp);

}

inline void Add(int val)
{
    Heap[++nr] = val;
    up( nr );
}

inline void Extract()
{
    if( nr <= 0 )
        return;
    sol += 1LL * Heap[1];
    Heap[1] = Heap[nr], --nr;
    down( 1 );
}

void Solve()
{
    int i, j;
    if( !l )
    {
        printf("%lld", sol);
        return;
    }
    V[0].T = -1;
    for(i = n; i; --i)
    {
        j = i;
        while( V[i].T == V[j].T && j )
        {
             Add(V[j].lana); --j;
        }
        i = j + 1;

        for(j = 1; j <= V[i].T - V[i - 1].T; ++j)
            Extract();

    }
    printf("%lld", sol);
}

int main()
{
    Read();
    Solve();
    return 0;
}
