# include <cstdio>
# include <algorithm>
using namespace std;

FILE *f = freopen("comb.in", "r", stdin);
FILE *g = freopen("comb.out", "w", stdout);

int n, m;

const long long MOD = 1000000009;

long long power(long long a, long long e)
{
    long long rez = 1;
    long long x = a;

    for (long long i = 0; (1LL<<i) <= e; i++)
    {
        if ((1LL<<i) & e)
        {
            rez *= x;
            rez %= MOD;
        }

        x *= x;
        x %= MOD;
    }

    return rez;
}

void read()
{
    scanf("%d %d", &n, &m);
}

void comb(int n, int m)
{
    long long rez = 1;

    int minim = min(n, m);
    int maxim = max(n, m);

    maxim = 2 * minim - 2 + maxim - minim;

    minim --;

    //printf("%d %d\n", maxim, minim);
    //maxim = 18;
    //minim = 4;

    for (int i = minim + 1; i<= maxim; i++)
    {
        if(i <= maxim - minim) {
            continue;
        }
        rez *= 1LL*i;
        rez %= MOD;
    }

    for (int i=1; i<=maxim - minim; i++)
    {
        if(i >= minim + 1) {
            continue;
        }
        rez *= power(1LL*i, MOD-2);
        rez %= MOD;
    }

    printf("%lld\n", (1LL * 5 * power(5LL, MOD - 2)) % MOD);
    printf("%lld\n", rez);
}

int main()
{
    read();
    comb(n, m);
    return 0;
}
