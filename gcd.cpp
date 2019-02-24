#include <cstdio>

using namespace std;

FILE *fin=freopen("gcd.in","r",stdin);
FILE *fout=freopen("gcd.out","w",stdout);

long long int Mod;

long long int gcd(long long int a,long long int b)
{
    long long int r;
    while(b)
    {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

long long int Pow(long long int a,long long int b)
{
    long long int sol = 1, p2 = 2 % Mod;

    for(long long int i = 1; i <= b ; i <<= 1 )
    {
        if( b & i )
        {
            sol = 1LL * (sol * p2) % Mod;
        }
        p2 = 1LL * (p2 * p2) % Mod;
    }
    return sol;
}

int main()
{
    long long int t, m, n, k;

    for(scanf("%lld", &t); t > 0 ; --t )
    {
        scanf("%lld%lld%lld", &m, &n, &Mod);
        k = gcd(m , n);
        k = Pow(2, k);
        if( k == 0 )
            k = Mod - 1;
        else
            --k;
        printf("%lld\n", k);
    }

    return 0;
}
