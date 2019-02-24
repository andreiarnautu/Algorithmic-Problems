#include <cstdio>
#include <algorithm>
#define Dim 53
#define MaxC 2503

using namespace std;

FILE *fin=freopen("luna.in","r",stdin);
FILE *fout=freopen("luna.out","w",stdout);

int m, n, tasks;
int F[MaxC], A[Dim][Dim], Best[MaxC][Dim], H[Dim][Dim], O[Dim][Dim];
struct matrix{int ori, ver;} Part[Dim][Dim];


void Read()
{
    scanf("%d%d", &m, &n);
    for(int i = 1 ; i <= m ; ++i )
        for(int j = 1;  j <= n ; ++j )
        {
            scanf("%d", &A[i][j]);
            F[A[i][j]] = 1;
        }
}

inline int Max(int a, int b, int c)
{
    if( a >= b && a >= c )
        return a;
    if( b >= a && b >= c )
        return b;
    return c;
}

void Solve_Dynamic()
{
    int i, j, orizontal, vertical;

    for( i = 1 ; i <= m ; i++ )
        for( j = 1 ; j <= n ; ++j )
        {
            if( A[i][j] == A[i - 1][j] )
                H[i][j] = H[i - 1][j] + 1;
            else
                H[i][j] = 0;

            if( A[i][j - 1] == A[i][j] )
                O[i][j] = O[i][j - 1] + 1;
            else
                O[i][j] = 0;
        }

    for( i = 1 ; i <= m ; ++i )
        for( j = 1 ; j <= n ; ++j )
        {
            vertical = H[i][j] + 1;
            for(int l = O[i][j] ; l >= 0 ; --l )
            {
                orizontal = O[i][j] - l + 1;
                vertical = min( vertical, H[i][j - O[i][j] + l] + 1 );
                Best[A[i][j]][orizontal] = max( Best[A[i][j]][orizontal] , vertical);
                Best[A[i][j]][vertical] = max( Best[A[i][j]][vertical] , orizontal);
            }

        }

    int maxim;

    for( i = 1 ; i < MaxC - 1 ; ++i )
    {
        maxim = 0;
        for( j = Dim - 2 ; j > 0 ; --j )
        {
             Best[i][j] = max(maxim, Best[i][j]);
             maxim = Best[i][j];
        }
    }

    /*for( i = 1 ; i <= m ; ++i )
    {
        for( j = 1 ; j <= n ; ++j )
            printf("%d ",H[i][j]);
        printf("\n");
    }*/

    /*for( i = 1 ; i <= 7 ; ++i )
    {
        for(j = 1 ; j <= 7 ; ++j )
            printf("%d ", Best[i][j]);
        printf("\n");
    }*/
}

void Answer_Query()
{
    int k, d1, d2;

    scanf("%d%d%d", &k, &d1, &d2);

    if( k > 2500 )
    {
        printf("Tara de provenienta nu are parcele pe Luna!\n");
        return;
    }

    if( !F[k] )
    {
        printf("Tara de provenienta nu are parcele pe Luna!\n");
        return;
    }

    if( d1 > 50 || d2 > 50 )
    {
        printf("Cererea nu poate fi satisfacuta!\n");
        return;
    }

    else if( Best[k][d1] >= d2 || Best[k][d2] >= d1 )
    {
        printf("Cererea poate fi satisfacuta!\n");
        return;
    }
    printf("Cererea nu poate fi satisfacuta!\n");
}

int main()
{
    Read();
    Solve_Dynamic();

    scanf("%d", &tasks);
    for(int i = 1 ; i <= tasks ; ++i )
        Answer_Query();
    return 0;
}
