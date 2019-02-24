#include <cstdio>

using namespace std;

FILE *fin = freopen("numere5.in","r",stdin);
FILE *fout = freopen("numere5.out","w",stdout);

long long int S, Sp, Diff;
long long int x, cnt, N;


int main()
{
    scanf("%lld", &N);

    S = 1ll * ( N * N ) * ( N * N + 1 ) / 2;

    for(long long int i = 1 ; i <= N * N ; ++i )
    {
        scanf("%lld", &x);
        Sp += x;
        if( !x )
            ++cnt;
    }

    Diff = 1ll * ( S - Sp );
    Diff = 1ll * ( Diff - ( cnt * (cnt + 1) / 2 ) );
    Diff = 1ll * ( Diff / cnt);

    printf("%lld %lld", Diff + 1 , Diff + cnt);

    return 0;
}
