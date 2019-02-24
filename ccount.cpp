#include <cstdio>
#define MaxN 1 << 17
#define Mod 9007

using namespace std;

FILE *fin=freopen("ccount.in","r",stdin);
FILE *fout=freopen("ccount.out","w",stdout);

int cnt, n, p;
int F[MaxN], Value[MaxN];

int main()
{
    int i, x;

    scanf("%d%d", &n, &p);
    for( i = 1 ; i <= p ; ++i )
    {
        scanf("%d", &x);
        Value[x] = 1;
    }

    F[n] = 1;

    for( i = n ; i > 2 ; --i )
    {
        if( !Value[i] )
        {
            cnt = (cnt + F[i]) % Mod;
            F[i - 1] = (F[i] + F[i - 1]) % Mod;
            F[i - 2] = (F[i] + F[i - 2]) % Mod;
        }
    }

    printf("%d", cnt);

    return 0;
}
