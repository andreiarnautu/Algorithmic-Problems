#include <cstdio>
#define DIM 1000300
using namespace std;
FILE *fin=freopen("curcubeu.in","r",stdin);
FILE *fout=freopen("curcubeu.out","w",stdout);

int A[DIM], B[DIM], C[DIM], Next[DIM], Color[DIM];
int n;

void Read()
{
    scanf("%d %d %d %d", &n, &A[1], &B[1], &C[1]);

    for(int i = 2; i < n ; ++i)
    {
        A[i] = ( 1LL * A[i - 1] * i ) % n;
        B[i] = ( 1LL * B[i - 1] * i ) % n;
        C[i] = ( 1LL * C[i - 1] * i ) % n;
    }
}

inline int MIN(int a, int b)
{
    return (a > b ? b : a);
}

inline int MAX(int a, int b)
{
    return (a > b ? a : b);
}

void Solve()
{
    int i, j, first, last, jj;

    for(i = n; i > 0; --i)
    {
        first = MIN(A[i], B[i]), last = MAX(A[i], B[i]);

        for(j = first; j <= last; ++j)
        {
            if( !Next[j] )
            {
                Color[j] = C[i];
                Next[j] = last + 1;
            }
            else
            {
                jj = Next[j];
                if( Next[j] < last + 1 )
                    Next[j] = last + 1;
                j = jj - 1;
            }
        }
    }

    for(i = 1; i < n; ++i)
        printf("%d\n", Color[i]);
}

int main()
{
    Read();
    Solve();
    return 0;
}
