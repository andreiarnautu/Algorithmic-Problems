// Lacusta
#include <cstdio>
#include <algorithm>
#define Dim 251
using namespace std;

FILE *fin=freopen("lacusta.in","r",stdin);
FILE *fout=freopen("lacusta.out","w",stdout);

short int A[Dim][Dim], N, M;
unsigned short B[Dim][Dim];


void Read()
{
    scanf("%d%d", &M, &N);
    for(int i = 1 ; i <= M ; ++i )
        for(int j = 1 ; j <= N ; ++j )
            scanf("%d", &A[i][j]);
}

void Solve()
{
    int Min1, Min2, j1 , j2;
    for(int i = 2 ; i <= N ; ++i )
        B[1][i] = A[1][i] + A[1][1];
    B[1][1] = 100000;

    for(int i = 2 ; i <= M ; ++i )
    {
        Min1 = Min2 = 1000000;
        for(int j = 1 ; j <= N ; ++j )
        {
            if( B[i - 1][j] + A[i][j] <= Min1 )
            {
                swap( j1, j2 );
                swap( Min1 , Min2 );
                Min1 = B[i - 1][j] + A[i][j];
                j1 = j;
            }
            else if( B[i - 1][j] + A[i][j] <= Min2 )
            {
                Min2 = B[i - 1][j] + A[i][j];
                j2 = j;
            }
        }

        for(int j = 1 ; j <= N ; ++j )
        {
            if( j == j1 )
                B[i][j] = Min2 + A[i][j];
            else
                B[i][j] = Min1 + A[i][j];
        }

    }

    /*for(int i = 1 ; i <= M ; ++i )
    {
        for(int j = 1 ; j <= N ; ++j )
            printf("%d ", B[i][j]);
        printf("\n");
    }*/

    printf("%d", B[M][N] );
}

int main()
{
    Read();
    Solve();
}
