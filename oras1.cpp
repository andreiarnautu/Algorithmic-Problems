#include <cstdio>
#define Dim 210
using namespace std;
FILE *fin=freopen("oras1.in","r",stdin);
FILE *fout=freopen("oras1.out","w",stdout);
int A[Dim][Dim], N, M;
int B[Dim][Dim], Nr;
int C[Dim][Dim], Max, Arie;

void Read()
{
    char c;
    scanf("%d%d", &N, &M);
    getchar();
    for(int i = 1 ; i <= N ; ++i )
    {
        for(int j = 1 ; j <= M ; ++j )
        {
            scanf("%c", &c);
            if( c == '.' )
                A[i][j] = -1;
            if( c == 'P' )
                A[i][j] = -2;
            if( c == 'C' )
                A[i][j] = -3;
            if( c == 'S' )
                A[i][j] = -4;
            C[i][j] = B[i][j] = A[i][j];
        }
        getchar();
    }
}

int Check(int x, int y)
{
    if( A[x - 1][y - 1] == -1 )
        return 1;
    if( A[x - 1][y] == - 1 )
        return 1;
    if( A[x - 1][y + 1] == -1 )
        return 1;
    if( A[x][y - 1] == -1 )
        return 1;
    if( A[x][y + 1] == -1 )
        return 1;
    if( A[x + 1][y - 1] == -1 )
        return 1;
    if( A[x + 1][y] == -1 )
        return 1;
    if( A[x + 1][y + 1] == -1 )
        return 1;
    return 0;
}

void Solve1()
{
    int Sol = 0;
    for(int i = 1 ; i <= N ; ++i )
        for(int j = 1 ; j <= M ; ++j )
        {
            if( A[i][j] == -1 )
                continue;
            if( Check(i , j) )
                ++Sol;
        }
    printf("%d ", Sol);
}

void Fill(int x, int y)
{
    B[x][y] = 1;
    if( B[x - 1][y] == -3 )
        Fill(x - 1, y);
    if( B[x][y - 1] == -3 )
        Fill(x, y - 1);
    if( B[x][y + 1] == -3 )
        Fill(x, y + 1);
    if( B[x + 1][y] == -3 )
        Fill(x + 1, y);
}

void Solve2()
{
    for(int i = 0 ; i <= N + 1 ; ++i )
        for(int j = 0 ; j <= M + 1 ; ++j )
            if( B[i][j] == -3 )
            {
                ++Nr;
                Fill(i , j);
            }
    printf("%d ",Nr);
}

void Fill2(int x, int y)
{
    ++Arie;
    C[x][y] = 1;
    if( C[x - 1][y] == -2 )
        Fill2(x - 1, y);
    if( C[x + 1][y] == -2 )
        Fill2(x + 1, y);
    if( C[x][y - 1] == -2 )
        Fill2(x, y - 1);
    if( C[x][y + 1] == -2 )
        Fill2(x, y + 1);
}

void Solve3()
{
    for(int i = 1 ; i <= N ; ++i )
        for(int j = 1; j <= M ; ++j )
            if( C[i][j] == -2 )
            {
             //   printf("%d %d\n",i ,j);
                Arie = 0;
                Fill2(i , j);
                if( Arie > Max )
                    Max = Arie;
            }
    printf("%d\n", Max);
}

int main()
{
    Read();
    for(int i = 0 ; i <= M + 1 ; ++i )
        B[0][i] = A[0][i] = A[N + 1][i] = -1;
    for(int i = 0 ; i <= N + 1 ; ++i )
        B[i][0] = A[i][0] = A[i][M + 1] = -1;
    Solve1();
    Solve2();
    Solve3();
    return 0;
}
