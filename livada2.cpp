#include <cstdio>
#include <algorithm>
#define DIM 301
using namespace std;
FILE *fin=freopen("livada2.in","r",stdin);
FILE *fout=freopen("livada2.out","w",stdout);

int DP[DIM][DIM][DIM], Max[DIM][DIM];
int best, n, m;

void Solve()
{
    int i, j, l, sum, avantaj;
    scanf("%d %d ", &n, &m);
    best = -1000000;

    for( i = 1; i <= n; ++i )
        for( j = 1; j <= m; ++j )
        {
            scanf("%d ", &DP[i][j][1]);
            best = max( best, DP[i][j][1] );
            Max[i][j] = -1000000;
        }

    for( i = 1; i <= n; ++i )
        for(j = 1; j <= m; ++j)
        {
            sum = DP[i][j][1];
            avantaj = Max[i - 1][j];
            for(l = 2; l <= j; ++l)
                {
                    sum += DP[i][j - l + 1][1];
                    avantaj = max( avantaj, Max[i - 1][j] );
                    DP[i][j][l]
                }
        }



}

int main()
{
    int t;
    for(scanf("%d", &t); t > 0; --t)
        Solve();
    return 0;
}
