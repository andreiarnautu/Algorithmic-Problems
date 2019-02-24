#include <cstdio>
#include <cstring>
using namespace std;
FILE *fin=freopen("operatii2.in","r",stdin);
FILE *fout=freopen("operatii2.out","w",stdout);

int Best[10003], List[10003][5];
int A[203][203];

void Compute()
{
    int i, j, l;

    memset(Best, -1, sizeof(Best));
    for(i = 0; i <= 100; ++i)
    {
        Best[i * i] = 1;
        List[i * i][1] = i;
    }

    for(i = 1; i < 10000; ++i)
        if( Best[i] == 1 )
            for(j = 1; j <= 100 && i + j * j <= 10000; ++j)
                if( Best[j * j + i] == -1 )
                {
                    Best[j * j + i] = 2;
                    List[j * j + i][1] = List[i][1], List[j * j + i][2] = j;
                }

    for(i = 1; i < 10000; ++i)
        if( Best[i] == 2 )
            for(j = 1; j <= 100 && i + j * j <= 10000; ++j)
                if( Best[j * j + i] == -1 )
                {
                    Best[j * j + i] = 3;
                    List[j * j + i][1] = List[i][1], List[j * j + i][2] = List[i][2], List[j * j + i][3] = j;
                }

    for(i = 1; i < 10000; ++i)
        if( Best[i] == 3 )
            for(j = 1; j <= 100 && i + j * j <= 10000; ++j)
                if( Best[i + j * j] == -1 )
                {
                    Best[j * j + i] = 4;
                    for(l = 1; l <= 3; ++l)
                        List[j * j + i][l] = List[i][l];
                    List[j * j + i][4] = j;
                }
}

int main()
{
    Compute();
    int l, i, j, n, m, BIG = 0;
    scanf("%d %d ", &m, &n);
    for(i = 1; i <= m ; ++i)
        for(j = 1; j <= n ; ++j)
        {
            scanf("%d", &A[i][j]);
            if( BIG < Best[A[i][j]] )
                BIG = Best[A[i][j]];
        }
    printf("%d\n", BIG);

    for(l = 1; l <= BIG; ++l)
        for(i = 1; i <= m ; ++i)
        {
            for(j = 1; j <= n ; ++j)
                printf("%d ", List[A[i][j]][l]);
            printf("\n");
        }
}
