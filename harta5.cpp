#include <cstdio>
#define Dim 3000

using namespace std;

FILE *fin=freopen("harta5.in","r",stdin);
FILE *fout=freopen("harta5.out","w",stdout);

int A[Dim][Dim], Lin[Dim], Col[Dim];
int N , M , K , Max, X[Dim], Y[Dim];

void Solve1()
{
    scanf("%d%d%d", &N, &M, &K);

    int x1, y1, x2, y2;
    for(int i = 1 ; i <= K ; ++i )
    {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        X[i] = ( x2 - x1 + 1 ) ;
        Y[i] = ( y2 - y1 + 1 ) ;
        if( X[i] == Y[i] && Max < X[i] )
            Max = X[i];
    }

    printf("%d ",Max * Max);

    int cnt = 0;
    for(int i = 1 ; i <= K ; ++i )
    {
        if( X[i] + 1 < Max && Y[i] + 1 < Max )
            ++cnt;
    }

    printf("%d", cnt);
}

void Solve2()
{
    scanf("%d%d%d", &N, &M, &K);

    int x1, x2, y1, y2, j;
    for(int i = 1 ; i <= K ; ++i )
    {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        for( j = y1 ; j <= y2 ; ++j )
            Col[j] = A[x1][j] = A[x2][j] = 1;
        for( j = x1 ; j <= x2 ; ++j )
            Lin[j] = A[j][y1] = A[j][y2] = 1;
    }

    bool ok = 0;
    for(int i = 1 ; i <= M ; ++i )
    {
        if( Col[i] == 1 )
            ok = 1;
        if( i > 1 && Col[i] == 0 && ( Col[i - 1] == 0 || Col[i - 1] == -1  ) )
            Col[i] = -1;
    }

    ok = 0;
    for(int i = 1 ; i <= N ; ++i )
    {
        if( Lin[i] == 1 )
            ok = 1;
        if( i > 1 &&  Lin[i] == 0 && ( Lin[i - 1] == 0 || Lin[i - 1] == -1  ) )
            Lin[i] = -1;
    }

    /*for(int i = 1 ; i <= N ; ++i )
    {
        for( j = 1 ; j <= M ; ++j )
            printf("%d ",A[i][j]);
        printf("\n");
    }*/

    for(int i = 1 ; i <= N ; ++i )
    {
        if( Lin[i] != -1 )
        {
            for( j = 1 ; j <= M ; ++j )
                if( Col[j] != -1 )
                    printf("%d ", A[i][j]);
            printf("\n");
        }
    }
}

int main()
{
    int p;
    scanf("%d", &p);

    if( p == 1 )
        Solve1();

    else
        Solve2();

    return 0;
}
