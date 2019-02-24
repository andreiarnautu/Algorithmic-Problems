#include <cstdio>
#define Mod 104659

using namespace std;

FILE *fin=freopen("nrcuv.in","r",stdin);
FILE *fout=freopen("nrcuv.out","w",stdout);

 bool A[27][27];

 int m, n;
 int No[1003][28];


void Read()
{
    char c1, c2, c3;
    scanf("%d%d", &n, &m);
    getchar();
    for(int i = 1 ; i <= m ; ++i )
    {
        scanf("%c%c%c", &c1, &c3, &c2);
        getchar();
        //printf("%d %d\n", c1 - 96, c2 - 96);
        A[c1 - 96][c2 - 96] = A[c2 - 96][c1 - 96] = 1;
    }
}

void Solve_Dynamic()
{
    for(int i = 1 ; i <= 26 ; ++i )
        No[1][i] = 1;

    /*for(int i = 1 ; i <= 6 ; ++i )
    {
        for(int j = 1 ; j <= 6 ; ++j )
            printf("%d ",A[i][j]);
        printf("\n");
    }*/

    for(int i = 2 ; i <= n ; ++i )
        for(int j = 1 ; j <= 26 ; ++j )
        {
            for(int l = 1; l <= 26 ; ++l )
                if( !A[j][l] )
                    No[i][j] += No[i - 1][l];
            No[i][j] = No[i][j] % Mod;
        }
}

void Write()
{
    int Sum = 0;
    for(int i = 1 ; i <= 26 ; ++i )
        Sum += No[n][i];
    Sum = Sum % Mod;
    printf("%d", Sum);
}

int main()
{
    Read();
    Solve_Dynamic();
    Write();
    return 0;
}
