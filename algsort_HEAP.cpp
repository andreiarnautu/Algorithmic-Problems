/*
    How about a coding trick?
*/
#include <cstdio>
#include <algorithm>
#define DIM 500500
using namespace std;
FILE *fin=freopen("algsort.in","r",stdin);
FILE *fout=freopen("algsort.out","w",stdout);

int heap[DIM];
int n, nr;

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
    int key = heap[ nod ];
    while( nod > 1 && key > heap[ father(nod) ] )
    {
        heap[ nod ] = heap[ father(nod) ];
        nod = father( nod );
    }
    heap[ nod ] = key;
}

inline void down(int nod)
{
    int son = 1;
    while( son )
    {
        son = 0;
        if( left_son(nod) <= nr )
        {
            son = left_son( nod );
            if( right_son( nod ) <= nr && heap[ right_son(nod) ] > heap[ left_son(nod) ] )
                son = right_son( nod );
            if( heap[ son ] < heap[ nod ] )
                son = 0;
        }
        if( son )
        {
            swap( heap[son], heap[nod] );
            nod = son;
        }
    }
}

inline void Add(int x)
{
    heap[++nr] = x;
    up( nr );
}

int main()
{
    int i, x;
    scanf("%d", &n);
    for(i = 1; i <= n; ++i)
    {
        scanf("%d", &x);
        Add( x );
    }
    for(i = n; i > 1; --i)
    {
        swap( heap[1], heap[i] );
        --nr;
        down( 1 );
    }
    for(i = 1; i <= n; ++i)
        printf("%d ", heap[i]);
    return 0;
}
