#include <cstdio>
#include <cstring>
#define Dim 103
using namespace std;
FILE *fin=freopen("alpinist.in","r",stdin);
FILE *fout=freopen("alpinist.out","w",stdout);
int M , N, A[Dim][Dim], B[Dim][Dim], Lin[10010], Col[10010];

int Max, c1, c2, c3, c4 , Length, Path[Dim * Dim];

void Read()
{
    scanf("%d%d", &M, &N);
    for(int i = 1 ; i <= M ; ++i )
        for(int j = 1 ; j <= N ; ++j )
            scanf("%d", &A[i][j]);
}

int Check(int x, int y)
{
    if( y == 0 )
        return 0;
    if( y - x > 100 )
        return 0;
    return 1;
}

void Lee(int x, int y)
{
    int p , u, l , c , ok = 0 , x2 , y2 , k;
    for(int i = 1 ; i <= M ; ++i )
        for(int j = 1 ; j <= N ; ++j )
            B[i][j] = 0;
    B[x][y] = 1;
    p = u = 0;
    Lin[0] = x ; Col[0] = y;
    while( p <= u )
    {
        l = Lin[p];
        c = Col[p];
        if( B[l - 1][c] == 0 && l > 1 && Check( A[l][c] , A[l - 1][c] ))
        {
            B[l - 1][c] = B[l][c] + 1;
            ++u;
            Lin[u] = l - 1;
            Col[u] = c;
            if( (A[l - 1][c] > Max) || ( A[l - 1][c] == Max && B[l - 1][c] - 1 < Length) )
            {
                ok = 1;
                x2 = l - 1;
                y2 = c;
                Max = A[l - 1][c];
               //  printf("%d ", Max);
            }
        }

        if( B[l + 1][c] == 0 && l < M && Check( A[l][c], A[l + 1][c] ))
        {
            B[l + 1][c] = B[l][c] + 1;
            ++u;
            Lin[u] = l + 1;
            Col[u] = c;
            if( (A[l + 1][c]) > Max || ( A[l + 1][c] == Max && B[l + 1][c] - 1 < Length ) )
            {
                ok = 1;
                x2 = l + 1;
                y2 = c;
                Max = A[l + 1][c];
               //  printf("%d ", Max);
            }
        }

        if( B[l][c - 1] == 0 && c > 1 && Check( A[l][c] , A[l][c - 1] ))
        {
            B[l][c - 1] = B[l][c] + 1;
            ++u;
            Lin[u] = l;
            Col[u] = c - 1;
            if( (A[l][c - 1] > Max) || ( A[l][c - 1] == Max && B[l][c - 1] - 1 < Length ) )
            {
                ok = 1;
                x2 = l;
                y2 = c - 1;
                Max = A[l][c - 1];
                //printf("%d ", Max);
            }
        }

        if( B[l][c + 1] == 0 && c < N && Check( A[l][c], A[l][c + 1] ))
        {
            B[l][c + 1] = B[l][c] + 1;
            ++u;
            Lin[u] = l;
            Col[u] = c + 1;
            if( A[l][c + 1] > Max || ( A[l][c + 1] == Max && B[l][c + 1] - 1 < Length ) )
            {
                ok = 1;
              //  printf("%d ", Max);
                x2 = l;
                y2 = c + 1;
                Max = A[l][c + 1];
            }
        }
        ++p;
    }
   /* for(int i = 1 ; i <= M ; ++i )
    {
        for(int j = 1 ; j <= N ; ++j )
            printf("%d ",B[i][j]);
        printf("\n");
    }*/
    if( ok )
    {
        c1 = x;
        c2 = y;
        c3 = x2;
        c4 = y2;
        Max = A[x2][y2];
        Length = B[x2][y2] - 1;
        k = Length + 1;
        while( k > 1 )
        {
            if( B[x2 - 1][y2] == B[x2][y2] - 1 && Check( A[x2 - 1][y2] , A[x2][y2] ))
            {
                --x2;
                Path[--k] = 1;
            }
            else if( B[x2 + 1][y2] == B[x2][y2] - 1 && Check( A[x2 + 1][y2] , A[x2][y2] ) )
            {
                ++x2;
                Path[--k] = 2;
            }
            else if( B[x2][y2 - 1] == B[x2][y2] - 1 && Check( A[x2][y2 - 1] , A[x2][y2] ) )
            {
                --y2;
                Path[--k] = 3;
            }
            else
            {
                ++y2;
                Path[--k] = 4;
            }
        }
    }
}

void Solve()
{
    for(int i = 1 ; i <= M ; ++i )
        for(int j = 1 ; j <= N ; ++j )
            if( A[i][j] == 0 )
                Lee( i , j );
    printf("%d\n",Max);
    printf("%d %d %d %d\n", c1 , c2, c3, c4);
    printf("%d\n", Length);
    for(int i = 1 ; i <= Length ; ++i )
    {
        if( Path[i] == 1 )
            printf("S ");
        if( Path[i] == 2 )
            printf("N ");
        if( Path[i] == 3 )
            printf("E ");
        if( Path[i] == 4 )
            printf("W ");
    }
}

int main()
{
    Read();
    Solve();
    return 0;
}
