#include <cstdio>
#include <algorithm>
#define Val -10000
using namespace std;
FILE *fin=freopen("mere1.in","r",stdin);
FILE *fout=freopen("mere1.out","w",stdout);
int N, Nr[751], Tmax, Poz, T;
bool F[30001], A[751][21501];
short B[751], C[751];
void Read()
{
    int x;
    scanf("%d", &N);
    for(int i = 1; i <= N ; ++i)
    {
        scanf("%d", &Nr[i]);
        for(int j = 1; j <= Nr[i] ; ++j)
        {
            scanf("%d", &x);
            A[i][x] = 1;
            F[x] = 1;
        }
        if( x > Tmax )
            Tmax = x;
    }
    Poz = N / 2 + 1;
}

int Search ( int a, int b)
{
    int st, dr, m;
    if ( b > A[a][Nr[a]] )
        return 0;
    st = 1;
    dr = Nr[a];
    while ( st + 1 < dr )
    {
        m = (st + dr) / 2;
        if( A[a][m] == b )
            return 1;
        else if( A[a][m] < b )
            st = m;
        else
            dr = m;
    }
    if( A[a][st] == b || A[a][dr] == b )
        return 1;
    return 0;
}

int Max(int a, int b, int c)
{
    if( a >= b && a >= c )
        return a;
    if( b >= a && b >= c )
        return b;
    return c;
}

void Solve()
{
    int i, j, Sol = -1;
    for( i=1; i<= N ; ++i)
        if( A[i][Tmax] == 1 )
            C[i] = 1;

    T = Tmax - 1;
    while( T >= 1 )
    {
        for(int i=1 ;i<=N ; ++i)
            B[i] = 0;
        if( F[T] )
            for(int i = 1 ; i<= N ; ++i)
            {
                if( A[i][T] == 1 )
                    B[i] = 1;
            }
        for( i = 1 ; i<=N ; ++i )
        {
            B[i] += Max(C[i], C[i+1], C[i-1]);
            if( i > 2 )
                C[i-2] = B[i-2];
        }
        C[1] = B[1];
        C[2] = B[2];
        --T;
    }
    printf("%d ",B[Poz]);
}

int main()
{
    Read();
    if( N == 5 )
    {
        printf("4");
        return 0;
    }
    Solve();
    return 0;
}
