// It's not the load that breaks you down, it's the way you carry it.
#include <cstdio>
#include <ctime>
using namespace std;
FILE *fin=freopen("intersect.in","r",stdin);
FILE *fout=freopen("intersect.out","w",stdout);
//FILE *fout=freopen("intersect.in","w",stdout);

bool DP[151][151 * 151 / 2];

inline int min(int a, int b)
{
    return( a > b ? b : a );
}

void Gen()
{
    int n, m, i, j, l;
    n = 150;
    m = 150 * 150 / 2;

    DP[0][0] = 1;
    for(i = 0; i < n; ++i)
    {
        for(j = 0; j <= i * (i - 1) / 2; ++j)
        {
            if( DP[i][j] )
            {
                for(l = 1; i + l <= n && j + i * l <= m; ++l)
                    DP[i + l][j + i * l] = 1;
            }
        }
    }
}

void Solve()
{
    int n, m;
    scanf("%d %d ", &n, &m);

    if( DP[n][m] )
        printf("%d\n", m + n + 1);
    else
        printf("0\n");
}

int main()
{
    int teste;
    clock_t start, finish;
    start = clock();

    Gen();

    for(scanf("%d", &teste); teste > 0; --teste)
        Solve();

    finish = clock();
    //printf("%.4f", (float)(finish - start) / CLOCKS_PER_SEC);
    return 0;
}
