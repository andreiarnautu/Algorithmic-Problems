/*
    How about a coding trick?
*/
#include <cstdio>
#include <algorithm>
#define DIM 500500
using namespace std;
FILE *fin=freopen("algsort.in","r",stdin);
FILE *fout=freopen("algsort.out","w",stdout);

int n;
int A[DIM];

void Read()
{
    int i;
    scanf("%d", &n);
    for(i = 1; i <= n ; ++i)
        scanf("%d", &A[i]);
}

inline void Quick_Sort(int lo, int hi)
{
    int st = lo, dr = hi, aux = A[(lo + hi) / 2];
    do
    {
        while( st < hi && aux > A[st] )
            ++st;
        while( dr > lo && aux < A[dr] )
            --dr;
        if( st <= dr )
        {
            swap( A[st], A[dr] );
            ++st, --dr;
        }

    }while(st <= dr);
    if( lo < dr )
        Quick_Sort(lo, dr);
    if( hi > st )
        Quick_Sort(st, hi);
}

int main()
{
    Read();
    Quick_Sort(1, n);

    for(int i = 1; i <= n; ++i)
        printf("%d ", A[i]);
    return 0;
}
