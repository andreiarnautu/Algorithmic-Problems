#include <cstdio>
#include <algorithm>
#include <cstring>
#define DIM 180
using namespace std;
FILE *fin=freopen("origami.in","r",stdin);
FILE *fout=freopen("origami.out","w",stdout);

int A[DIM][DIM], B[DIM][DIM];
int n, m, k;

void Solve()
{
    int i, j, op, lat, d;

    scanf("%d %d", &op, &lat);

    if(op == 1)
    {
        d = max(m - lat, lat);
        for(i = 1; i <= d; ++i)
        {
            for(j = 1; j <= n ; ++j)
            {
                B[j][i] = 0;
                if( lat + i <= m )
                    B[j][i] += A[j][i + lat];
                if( lat - i + 1 >= 1 )
                    B[j][i] += A[j][lat - i + 1];
            }
        }
        m = max(lat, m - lat);
    }

    else
    {
        d = max(lat, n - lat);
        for(j = 1; j <= d; ++j)
        {
            for(i = 1; i <= m; ++i)
            {
                B[j][i] = 0;
                if( lat + j <= n )
                    B[j][i] += A[j + lat][i];
                if( lat - j + 1 >= 1 )
                    B[j][i] += A[lat - j + 1][i];
            }
        }
        n = max(lat, n - lat);
    }

    for(i = 1; i <= n ; ++i)
        for(j = 1; j <= m; ++j)
            A[i][j] = B[i][j];
}

int main()
{
    scanf("%d %d", &n, &k);
    m = n;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m ; ++j)
            A[i][j] = 1;

    for(int i = 1; i <= k ; ++i)
    {
        Solve();
        /*for(int i1 = 1; i1 <= n; ++i1)
        {
            for(int i2 = 1; i2 <= m; ++i2)
                printf("%d ", A[i1][i2]);
            printf("\n");
        }*/
    }


    int MAX = 0;
    for(int i = 1; i <= n ; ++i)
        for(int j = 1; j <= m ; ++j)
           if( A[i][j] > MAX )
                MAX = A[i][j];
    printf("%d %d %d", n, m, MAX);

    return 0;
}
