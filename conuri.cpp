#include <cstdio>
#include <algorithm>
#define DIM 100003
using namespace std;
FILE *fin=freopen("conuri.in","r",stdin);
FILE *fout=freopen("conuri.out","w",stdout);

int bestLen, DP[DIM];

int main()
{
    int n, a, b, x, y;
    scanf("%d", &n);

    for(int i = 1; i <= n; ++i)
    {
        scanf("%d %d ", &a, &b);
        x = DP[a], y = DP[b];
        DP[a] = max( x, y + 1 );
        DP[b] = max( y, x + 1 );
        bestLen = max( bestLen, DP[a] );
        bestLen = max( bestLen, DP[b] );
    }
    printf("%d", bestLen);
    return 0;
}
