// How about a coding trick?
#include <cstdio>
#include <algorithm>
#define MOD 32173
#define DIM 30030
using namespace std;
FILE *fin=freopen("ben.in","r",stdin);
FILE *fout=freopen("ben.out","w",stdout);

int F[DIM], Join[DIM], Total[DIM], PHI, Fact[DIM];
int n;

void Read()
{
    int i, x, y;
    scanf("%d", &n);

    for(i = 1; i <= n; ++i)
    {
        scanf("%d%d", &x, &y);
        ++Join[x];
        ++F[x], --F[y + 1];
    }

}

void Gen_Fact()
{
    int i;
    Fact[0] = 1;
    for(i = 1; i <= 30000; ++i)
        Fact[i] = (i * Fact[i - 1]) % MOD;
}

inline int Calc(int n, int k)
{
    int ret = Fact[n], p = PHI - 1, i, aux, val = 1;
    aux = (1LL * Fact[n - k]) % MOD;


    for(i = 1; i <= p; i <<= 1)
    {
        if(i & p)
            val = (1LL * val * aux) % MOD;
        aux = (aux * aux) % MOD;
    }
    ret = (ret * val) % MOD;
    return ret;
}

void Solve()
{
    int i, maxim = -1, ansCount = 1;
    for(i = 1; i <= 30000; ++i)
    {
        Total[i] = Total[i - 1] + F[i];
        maxim = max( maxim, Total[i] );
    }
    printf("%d ", maxim);

    PHI = MOD - 1;
    Gen_Fact();

    for(i = 1; i <= 30000; ++i)
        if( Join[i] > 0 )
        {
            ansCount = ( 1LL * ansCount * Calc(maxim - (Total[i] - Join[i]), Join[i]) ) % MOD;
        }
    printf("%d", ansCount);
}

int main()
{
    Read();
    Solve();
}
