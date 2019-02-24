// Algoritmiada 2015 runda 1 juniori
#include <cstdio>
#define Dim 300003
#define Mod 666013

using namespace std;

FILE *fin=freopen("minesweeper2.in","r",stdin);
FILE *fout=freopen("minesweeper2.out","w",stdout);

int N, V[Dim], A[Dim][4];


void Read()
{
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
        scanf("%d", &V[i]);
}

void First()
{
    if( V[1] == 0 )
        A[2][0] = 1;
    if( V[1] == 1 )
        A[2][1] = A[2][2] = 1;
    if( V[1] == 2 )
        A[2][3] = 1;
    if( V[1] == -1 )
        A[2][0] = A[2][1] = A[2][2] = A[2][3] = 1;
}

void Solve()
{
    for(int i = 2 ; i <= N ; ++i )
    {
        if( V[i] == 0 )
            A[i + 1][0] = A[i][0];

        else if( V[i] == 1 )
            A[i + 1][0] = A[i][2], A[i + 1][1] = A[i][0] , A[i + 1][2] = A[i][1];

        else if( V[i] == 2 )
            A[i + 1][1] = A[i][2], A[i + 1][2] = A[i][3] , A[i + 1][3] = A[i][1];

        else if( V[i] == 3 )
            A[i + 1][3] = A[i][3];

        else
        {
            A[i + 1][0] = ( A[i][0] + A[i][2] ) % Mod;
            A[i + 1][1] = ( A[i][0] + A[i][2] ) % Mod;
            A[i + 1][2] = ( A[i][3] + A[i][1] ) % Mod;
            A[i + 1][3] = ( A[i][3] + A[i][1] ) % Mod;
        }
    }

    if( V[N] == 0 )
        printf("%d", A[N][0]);

    else if( V[N] == 1 )
        printf("%d", ( A[N][1] + A[N][2] ) % Mod);

    else if( V[N] == 2 )
        printf("%d", A[N][3]);

    else if( V[N] == 3 )
        printf("0");

    else
        printf("%d", ( A[N][0] + A[N][1] + A[N][2] + A[N][3] ) %  Mod);


}

int main()
{
    Read();
    if( V[1] == 3 || V[N] == 3 )
    {
        printf("0");
        return 0;
    }
    First();
    Solve();
    return 0;
}
