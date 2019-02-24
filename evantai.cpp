/*
    Worg
*/
#include <cstdio>
#define zeros(x) ((x ^ (x - 1)) & x)
#define DIM 707
#define MaxSum 2020
#define MOD 30103
using namespace std;
FILE *fin=freopen("evantai.in","r",stdin);
FILE *fout=freopen("evantai.out","w",stdout);

int AIB[DIM][MaxSum], DP[DIM][MaxSum];
int v[DIM];
int n;

void Read()
{
    int i;
    scanf("%d", &n);
    for(i = 1; i <= n; ++i)
        scanf("%d", &v[i]);
}

inline void Add(int x, int y, int val)
{
    int i, j;
    for(i = x; i <= n; i += zeros(i))
        for(j = y; j <= 2000; j += zeros(j))
            AIB[i][j] = ( val + AIB[i][j] ) % MOD;
}

inline int Query(int x, int y)
{
    int i, j, ret = 0;
    for(i = x; i; i -= zeros(i))
        for(j = y; j; j -= zeros(j))
            ret += AIB[i][j];
    return (ret % MOD);
}

void Solve()
{
    int i, j, ans = 0, curent;
    for(i = n; i; --i)
    {
        for(j = i + 1; j <= n; j++)
        {
            DP[i][j] = Query(j - 1, v[i] + v[j] - 1) + 1;
            ans = ( ans + DP[i][j] ) % MOD;
        }

        for(j = i + 1; j <= n; ++j)
            Add(j, v[i] + v[j], DP[i][j]);

    }
    printf("%d", ans);
}

int main()
{
    Read();
    Solve();
    return 0;
}
