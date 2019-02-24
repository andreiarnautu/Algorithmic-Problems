#include <cstring>
#include <cstdio>
#define DIM 110
#define INF 1 << 30
using namespace std;
FILE *fin=freopen("lapte.in","r",stdin);
FILE *fout=freopen("lapte.out","w",stdout);

struct timp {
                int a, b;
            };
timp V[DIM];

int last[DIM][DIM], DP[DIM][DIM];
int n, L;

void Read()
{
    scanf("%d %d", &n, &L);
    for(int i = 1; i <= n; ++i)
        scanf("%d %d", &V[i].a, &V[i].b);
}

inline bool Check(int time)
{
    int i, j, k, val;

    for(i = 0; i <= n; ++i)
        for(j = 0; j <= L; ++j)
            DP[i][j] = -INF, last[i][j] = 0;

    DP[0][0] = 0;

    for(i = 1; i <= n; ++i)
        for(j = 0; j <= L; ++j)
            for(k = 0; k * V[i].a <= time && k <= L - j; ++k)
            {
                val = DP[i - 1][j] + ( time - k * V[i].a ) / V[i].b;
                if( val > DP[i][j + k] )
                {
                    DP[i][j + k] = val;
                    last[i][j + k] = j;
                }
            }
    return (DP[n][L] >= L);
}

void Write(int a1, int b1, int rez)
{
    int x, y;
    if( a1 == 0 )
        return;
    Write(a1 - 1, last[a1][b1], rez);

    x = b1 - last[a1][b1];
    y = ( rez - x * V[a1].a ) / V[a1].b;

    printf("%d %d\n", x, y);
}

void Solve()
{
    int rez = 100, p = 64;

    for(; p ; p >>= 1)
        if( rez > p && Check(rez - p) )
            rez -= p;
    printf("%d\n", rez);

    Check(rez);
    Write(n, L, rez);
}

int main()
{
    Read();
    Solve();
    return 0;
}
