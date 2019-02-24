#include <cstdio>
#define DIM 110
using namespace std;
FILE *fin=freopen("diferenta.in","r",stdin);
FILE *fout=freopen("diferenta.out","w",stdout);

int T[DIM][DIM];
int n, m;

void Read()
{
    scanf("%d %d ", &n, &m);
    for(int i = 1; i <= n ; ++i)
        for(int j = 1; j <= m; ++j)
            scanf("%d ", &T[i][j]);
}

inline int F(int x)
{
    int i, val, ret = 0;
    for(i = 1; i * i <= x; ++i)
        if( x % i == 0 )
        {
            val = x / i;
            if( (val - i) % 2 == 0 )
                ++ret;
        }
    return ret;
}

void Solve()
{
    int i, j;
    for(i = 1; i <= n; ++i)
    {
        for(j = 1; j <= m; ++j)
            printf("%d ", F(T[i][j]));
        printf("\n");
    }
}

int main()
{
    Read();
    Solve();
    return 0;
}
