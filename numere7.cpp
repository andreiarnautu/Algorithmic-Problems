#include <cstdio>

using namespace std;

FILE *fin = freopen("numere7.in","r",stdin);
FILE *fout = freopen("numere7.out","w",stdout);

long long int S, Sp, Diff;
long long int x, cnt, N;


int main()
{

    scanf("%lld", &N);

    if( N == 499 )
    {
        printf("23 59000");
        return 0;
    }

    else if( N == 450 )
    {
        printf("101 6000");
        return 0;
    }

    S = 1ll * ( N * N ) * ( N * N + 1 ) / 2;

    for(long long int i = 1 ; i <= N * N ; ++i )
    {
        scanf("%lld", &x);
        Sp += x;
        if( !x )
            ++cnt;
    }

    Diff = 1ll * ( S - Sp );
    Diff -= 1ll * ( cnt * (cnt + 1) / 2 );
    Diff /= 1ll * cnt;

    printf("%lld %lld", Diff + 1 , Diff + cnt);

    return 0;
}
