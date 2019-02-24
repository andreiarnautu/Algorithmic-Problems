// How about a coding trick?
#include <cstdio>
#include <bitset>
#define DIM 200000
using namespace std;
FILE *fin=freopen("dreptunghiuri.in","r",stdin);
FILE *fout=freopen("dreptunghiuri.out","w",stdout);

int Rad[DIM], Patrat[DIM];
bitset <DIM> viz;

void Gen()
{
    int i;
    for(i = 0; i <= 400; ++i)
        viz[i * i] = 1, Patrat[i] = i * i, Rad[i * i] = i;
}

inline long long int Find(int H, int W)
{
    int i, delta;
    long long ret = 1;

    for(i = 1; i < H; ++i)
    {
        delta = Patrat[W] - 4 * (i * H - Patrat[i]);
        if( delta >= 0 && viz[delta] == 1 )
        {
            if( delta == 0 && W % 2 == 0)
                ++ret;
            else if( delta > 0 && (Rad[delta] + W) % 2 == 0)
                ret += 2;
        }
    }
    return ret;
}

void Solve()
{
    int n, m, i, j;
    long long ansCount = 0;
    scanf("%d%d", &n, &m);
    --m, --n;

    for(i = 1; i <= n; ++i)
        for(j = 1; j <= m; ++j)
            ansCount += Find(i, j) * (n - i + 1) * (m - j + 1);

    printf("%lld", ansCount);
}

int main()
{
    Gen();
    Solve();
    return 0;
}
