/*
    Worg
*/

#include <cstdio>
#include <bitset>
using namespace std;

bitset < 100003 > ok;
int n, k, nr;
long long int S, stacked, sum;

int main()
{
    int i, x;
    FILE *fin=freopen("ksecv3.in","r",stdin);
    FILE *fout=freopen("ksecv3.out","w",stdout);

    scanf("%d %d", &n, &k);
    for(i = 1; i <= n; ++i)
    {
        scanf("%d", &x);
        S += x;
    }

    if( S % k )
    {
        printf("-1");
        return 0;
    }

    sum = S / k;
    S = 0;

    fin=freopen("ksecv3.in","r",stdin);
    fout=freopen("ksecv3.out","w",stdout);

    scanf("%d %d", &n, &k);
    for(i = 1; i <= n; ++i)
    {
        scanf("%d", &x);
        stacked += x;
        if( stacked > sum )
        {
            printf("-1");
            return 0;
        }
        if( stacked == sum )
            ok[ i ] = 1, stacked = 0;
    }

    for(i = 1; i <= n; ++i)
        if( ok[i] )
            printf("%d ", i);
    return 0;
}
