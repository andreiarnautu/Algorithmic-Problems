#include <cstdio>
#define Dim 103
#define MaxK 23

using namespace std;

FILE *fin=freopen("homm.in","r",stdin);
FILE *fout=freopen("homm.out","w",stdout);

int A[Dim][Dim], D[Dim][Dim][MaxK];
int M, N, K, x1, y1, x2, y2;


void Read()
{
    scanf("%d%d%d", &M, &N, &K);

    for(int i = 1 ; i <= M ; ++i )
        for(int j = 1 ; j <= N ; ++j )
            scanf("%d", &A[i][j]);

    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
}

void Solve_Dynamic()
{
    D[x1][y1][0] = 1;

    for(int l = 1 ; l <= K ; ++l )
        for(int i = 1 ; i <= M ; ++i )
            for(int j = 1 ; j <= N ; ++j )
            {
                if( A[i][j] )
                    continue;
                D[i][j][l] = D[i - 1][j][l - 1] + D[i + 1][j][l - 1] + D[i][j - 1][l - 1] + D[i][j + 1][l - 1];
            }
}

void Write()
{
    int Sum = 0 ;
    for(int l = 0 ; l <= K ; ++l )
        Sum += D[x2][y2][l];
    printf("%d", Sum);
}

int main()
{
    Read();
    Solve_Dynamic();
    Write();

    return 0;
}
