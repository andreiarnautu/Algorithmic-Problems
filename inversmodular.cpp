// How about a coding trick?
#include <cstdio>
using namespace std;
FILE *fin=freopen("inversmodular.in","r",stdin);
FILE *fout=freopen("inversmodular.out","w",stdout);

long long int a, n, p, aux;

inline long long int PHI(long long int x)
{
    long long int ret = x;
    for(long long i = 2 ; i * i <= x; ++i)
        if( x % i == 0 )
        {
            ret = (ret / i) * (i - 1);
            while( x % i == 0 )
                x /= i;
        }
    if( x > 1 )
        ret = (ret / x) * (x - 1);
    return ret;
}

int main()
{
    scanf("%lld %lld", &a, &n);
    p = PHI(n) - 1;

    aux = a;
    long long int sol = 1;

    for(long long int i = 1; i <= p; i <<= 1)
    {
        if( i & p )
            sol = (sol * aux) % n;
        aux = (aux * aux) % n;
    }
    printf("%lld", sol);
    return 0;
}
