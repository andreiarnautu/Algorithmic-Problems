#include <cstdio>
using namespace std;
FILE *fin=freopen("inginer.in","r",stdin);
FILE *fout=freopen("inginer.out","w",stdout);

int N, M, A[80][80], B[80][80], x, y, x1, y1, Lin[600], Col[6000];

void Read()
{
    scanf("%d%d", &N, &M);
    char c;
    getchar();
    for(int i = 1 ; i <= N ; ++i )
    {
        for(int j = 1 ; j <= M ; ++j )
        {
            c = getchar();
            if( c == 'X' )
                A[i][j] = -1;
        }
        getchar();
    }
}

void Solve()
{
    int p, u, a, b;
    for(int i = 0 ; i <= N + 1 ; ++i )
        for(int j = 0 ; j <= M + 1 ; ++j )
            B[i][j] = A[i][j];
    B[x][y] = 1;
    p = u = 1;
    Lin[1] = x, Col[1] = y;
    while( p <= u )
    {
        a = Lin[p];
        b = Col[p];
        if( B[a - 1][b] == 0 && a >= 1 )
        {
            B[a - 1][b] = B[a][b] + 1;
            ++u;
            Lin[u] = a - 1;
            Col[u] = b;
        }

        if( B[a][b - 1] == 0 && b >= 1 )
        {
            B[a][b - 1] = B[a][b] + 1;
            ++u;
            Lin[u] = a;
            Col[u] = b - 1;
        }

        if( B[a + 1][b] == 0 && a <= N )
        {
            B[a + 1][b] = B[a][b] + 1;
            ++u;
            Lin[u] = a + 1;
            Col[u] = b;
        }

        if( B[a][b + 1] == 0 && b <= M )
        {
            B[a][b + 1] = B[a][b] + 1;
            ++u;
            Lin[u] = a;
            Col[u] = b + 1;
        }
        if( a - 1 == x1 && b == y1 && a > 1 )
        {
            printf("%d\n", B[a][b]);
            return;
        }
        if( a == x1 && b - 1 == y1 && b > 1 )
        {
            printf("%d\n", B[a][b]);
            return;
        }
        if( a + 1 == x1 && b == y1 )
        {
            printf("%d\n", B[a][b]);
            return;
        }
        if( a == x1 && b + 1 == y1  )
        {
            printf("%d\n", B[a][b]);
            return;
        }
        ++p;
    }
   /* for(int i = 1 ; i <= M + 1 ; ++i )
    {
        for(int j = 1 ; j <= N + 1 ; ++j )
            printf("%d ",B[])
    }*/
    if( B[x1][y1] == 0 || B[x1][y1] == -1 )
    {
        printf("0\n");
    }
}

int main()
{
    Read();
    do
    {
        scanf("%d%d%d%d", &x, &y, &x1, &y1);
        if( x == 0 && y == 0 && x1 == 0 && y1 == 0 )
            break;
        else
            Solve();
    }
    while( ! ( x == 0 && y == 0 && x1 == 0 && y1 == 0 ) );
    return 0;
}
