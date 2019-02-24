#include <cstdio>
#define MaxN 103

using namespace std;

FILE *fin=freopen("lacuri.in","r",stdin);
FILE *fout=freopen("lacuri.out","w",stdout);

int A[MaxN][MaxN], B[MaxN][MaxN], N, cnt, maxlin, maxcol, lacuri, ok = 1;
int Lin[MaxN * MaxN] , Col[MaxN * MaxN];


void Read()
{
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
        for(int j = 1 ; j <= N ; ++j )
            scanf("%d", &A[i][j] );
}

void Fill(int x, int y)
{
    ++cnt;
    A[x][y] = -1;
    if( x > maxlin )
        maxlin = x;
    if( y > maxcol )
        maxcol = y;

    if( A[x - 1][y] == 1 )
        Fill(x - 1 , y);
    if( A[x + 1][y] == 1 )
        Fill(x + 1 , y);
    if( A[x][y - 1] == 1 )
        Fill(x , y - 1);
    if( A[x][y + 1] == 1 )
        Fill(x , y + 1);
}

void Solve_the_Problem()
{
    for(int i = 1 ; i <= N ; ++i )
        for(int j = 1 ; j <= N ; ++j )
            if( A[i][j] == 1 )
            {
                cnt = 0;
                maxlin = i;
                maxcol = j;
                Fill(i , j);
                if( maxlin - i == maxcol - j && cnt == (maxlin - i + 1) * (maxlin - i + 1) )
                    ++lacuri;
                else
                    ok = 0;
            }

    printf("%d\n", lacuri);

    if( !ok )
        return;


    for(int i = 1 ; i <= N ; ++i )
        for(int j = 1 ; j <= N ; ++j )
            B[i][j] = A[i][j];
    int p, u, x, y;
    p = u = 0;

    A[1][1] = 1;
    Lin[0] = Col[0] = 1;

    while (p <= u)
    {
        x = Lin[p];
        y = Col[p];

        if( x > 1 && A[x - 1][y] == 0 )
        {
            A[x - 1][y] = A[x][y] + 1;
            ++u;
            Lin[u] = x - 1;
            Col[u] = y;
            if( x - 1 == y && y == N )
                break;
        }

        if( x < N && A[x + 1][y] == 0 )
        {
            A[x + 1][y] = A[x][y] + 1;
            ++u;
            Lin[u] = x + 1;
            Col[u] = y;
            if( x + 1 == y && y == N )
                break;
        }

        if( y > 1 && A[x][y - 1] == 0 )
        {
            A[x][y - 1] = A[x][y] + 1;
            ++u;
            Lin[u] = x;
            Col[u] = y - 1;
            if( x == y - 1 && x == N )
                break;
        }

        if( y < N && A[x][y + 1] == 0 )
        {
            A[x][y + 1] = A[x][y] + 1;
            ++u;
            Lin[u] = x;
            Col[u] = y + 1;
            if( x == y + 1 && x == N )
                break;
        }

        ++p;
    }

    p = u = 0;
    Lin[0] = Col[0] = N;
    B[N][N] = 1;

    while (p <= u)
    {
        x = Lin[p];
        y = Col[p];

        if( x > 1 && B[x - 1][y] == 0 )
        {
            B[x - 1][y] = B[x][y] + 1;
            ++u;
            Lin[u] = x - 1;
            Col[u] = y;
            if( x - 1 == y && y == 1 )
                break;
        }

        if( x < N && B[x + 1][y] == 0 )
        {
            B[x + 1][y] = B[x][y] + 1;
            ++u;
            Lin[u] = x + 1;
            Col[u] = y;
            if( x + 1 == y && y == 1 )
                break;
        }

        if( y > 1 && B[x][y - 1] == 0 )
        {
            B[x][y - 1] = B[x][y] + 1;
            ++u;
            Lin[u] = x;
            Col[u] = y - 1;
            if( x == y - 1 && x == 1 )
                break;
        }

        if( y < N && B[x][y + 1] == 0 )
        {
            B[x][y + 1] = B[x][y] + 1;
            ++u;
            Lin[u] = x;
            Col[u] = y + 1;
            if( x == y + 1 && x == 1 )
                break;
        }

        ++p;
    }

    /*for(int i = 1 ; i <= N ; ++i )
    {
        for(int j = 1 ; j <= N ; ++j )
            printf("%d ",B[i][j]);
        printf("\n");
    }*/

    x = y = 1;

    printf("1 1\n");

    for(int i = 2 ; i <= A[N][N] ; ++i )
    {
        if( A[x - 1][y] == A[x][y] + 1 && A[x - 1][y] + B[x - 1][y] == A[N][N] + 1)
            --x;
        else if( A[x + 1][y] == A[x][y] + 1 && A[x + 1][y] + B[x + 1][y] == A[N][N] + 1)
            ++x;
        else if( A[x][y - 1] == A[x][y] + 1 && A[x][y - 1] + B[x][y - 1] == A[N][N] + 1)
            --y;
        else
            ++y;

        printf("%d %d\n", x , y);
    }

}


int main()
{
    Read();
    Solve_the_Problem();
    return 0;
}
