// Sorry for this. :))
#include <cstdio>
#include <algorithm>
#define Nmax 503
using namespace std;
FILE *fin = freopen("incadrare.in","r",stdin);
FILE *fout = freopen("incadrare.out","w",stdout);
int N, M, A[Nmax][Nmax], B[Nmax][Nmax];

void Read()
{
    double x, y;
    scanf("%d%d", &N, &M);
    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%lf%lf", &x, &y);
        A[(int)y][(int)x] ++;
    }
}

void Solve()
{
    int i, j, x1, x2, y1, y2, Sol;
    for( i = 0 ; i < Nmax ; ++i )
        for( j = 0 ; j < Nmax ; ++j )
        {
            B[i][j] = A[i][j];
            if( i > 0 )
                B[i][j] += B[i - 1][j];
            if( j > 0 )
                B[i][j] += B[i][j - 1];
            if( i > 0 && j > 0 )
                B[i][j] -= B[i - 1][j - 1];
        }
    for( i = 0 ; i < M ; ++i )
    {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if( x2 == 0 || y2 == 0 )
        {
            printf("0\n");
            continue;
        }
        Sol = B[y2 - 1][x2 - 1];
        if( y1 > 0 )
            Sol -= B[y1 - 1][x2 - 1];
        if( x1 > 0 )
            Sol -= B[y2 - 1][x1 - 1];
        if( y1 > 0 && x1 > 0 )
            Sol += B[y1 - 1][x1 - 1];
        printf("%d\n", Sol);
    }
}

int main()
{
    Read();
    Solve();
    return 0;
}
