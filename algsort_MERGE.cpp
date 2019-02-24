/*
    How about a coding trick?
*/
#include <cstdio>
#define DIM 500500
using namespace std;
FILE *fin=freopen("algsort.in","r",stdin);
FILE *fout=freopen("algsort.out","w",stdout);

int A[DIM];
int aux[DIM];
int n;

void Read()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &A[i]);
}

inline void Unite(int st, int m, int dr)
{
    int i = st, j = m + 1, k = 0;

    while( i <= m && j <= dr )
    {
        if( A[i] < A[j] )
            aux[++k] = A[i], ++i;
        else
            aux[++k] = A[j], ++j;
    }

    while( i <= m )
        aux[++k] = A[i], ++i;
    while( j <= dr )
        aux[++k] = A[j], ++j;

    for(int i = st; i <= dr; ++i)
        A[i] = aux[i - st + 1];
}

inline void Merge_Sort(int st, int dr)
{
    int m;
    if( dr > st )
    {
        m = (st + dr) / 2;
        Merge_Sort(st, m);
        Merge_Sort(m + 1, dr);
        Unite(st, m, dr);
    }
}

int main()
{
    Read();
    Merge_Sort(1, n);

    for(int i = 1; i <= n; ++i)
        printf("%d ", A[i]);
    return 0;
}
