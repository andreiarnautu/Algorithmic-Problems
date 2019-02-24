// How about a coding trick?
#include <cstdio>
#define DIM 2002
using namespace std;
FILE *fin=freopen("paralelograme.in","r",stdin);
FILE *fout=freopen("paralelograme.out","w",stdout);

int GCD[DIM][DIM], n, m;

inline int cmmdc(int x, int y)
{
    int r = 0;
    while( y )
    {
        r = x % y, x = y, y = r;
    }
    return x;
}

void Gen()
{
    int i, j, val, it;
    for(i = 0; i <= m; ++i)
        for(j = i + 1; j <= n; ++j)
            if( !GCD[i][j] )
            {
                val = cmmdc(i, j);
                GCD[i][j] = val;
                GCD[j][i] = val;
                for(it = 2; it * i <= n && it * j <= m ; ++it)
                    GCD[i * it][j * it] = val * it, GCD[j * it][i * it] = val * it;
            }
}

void Solve()
{
    int i, j;
    long long int ansCount = 0, val;
    scanf("%d%d", &n, &m);
    Gen();

    for(i = 2; i <= n + 1; ++i)
        for(j = 2; j <= m + 1; ++j)
        {
            val = 1LL * (i - 2) * (j - 2) + 1LL * i * j - 2 - 1LL * GCD[i - 1][j - 1];
            ansCount += 1LL * val * (n - i + 2) * (m - j + 2);
        }
    printf("%lld", ansCount);
}

int main()
{
    Solve();
    return 0;
}
