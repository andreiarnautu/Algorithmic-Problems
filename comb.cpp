#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin=freopen("comb.in","r",stdin);
FILE *fout=freopen("comb.out","w",stdout);
int M, N, x, F[130], K, V[130];
int A[260][130][100];

void Read()
{
    scanf("%d%d", &M, &N);
    for(int i = 1 ; i <= M ; ++i )
    {
        scanf("%d", &x);
        ++F[x];
    }
    for(int i = 0 ; i <= 127 ; ++i )
        if( F[i] )
            V[++K] = F[i];
}

int Max(int a, int b)
{
    if( a >= b )
        return a;
    return b;
}

void Suma(int a, int b, int c, int d)
{
    int i , t = 0;
    if( A[c][d][0] == 0 )
        return;
    for( i = 1 ; i <= A[a][b][0] || i <= A[c][d][0] || t ; ++i , t /= 10 )
        A[a][b][i] = ( t += A[a][b][i] + A[c][d][i] ) % 10;
    A[a][b][0] = i - 1;
}

void Solve()
{
    int i , j , p, l;
    for( i = 1 ; i <= K ; ++i )
        A[0][i][0] = A[0][i][1] = 1;
    for( i = 1 ; i <= K ; ++i )
    {
        p = i;
        while( p )
        {
            A[1][i][0]++;
            A[1][i][A[1][i][0]] = p % 10;
            p /= 10 ;
        }
    }
    for( i = 2 ; i <= N ; ++i )
    {
        if( V[1] >= i )
            A[i][1][0] = A[i][1][1] = 1;
        for( j = 2 ; j <= K ; ++j )
        {
            p = Max( 0 , i - V[j] );
            for( l = i ; l >= p ; --l )
                Suma( i , j , l , j - 1);
        }
    }
    for(int i = A[N][K][0] ; i > 0 ; --i )
        printf("%d",A[N][K][i]);
    printf("\n");
}

int main()
{
    Read();
    Solve();
    return 0;
}
