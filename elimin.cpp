#include <cstdio>
#include <algorithm>
#define DIM 600
using namespace std;
FILE *fin=freopen("elimin.in","r",stdin);
FILE *fout=freopen("elimin.out","w",stdout);

int Aux[DIM][DIM], A[DIM][DIM], n, m, c, r, ans;
int V[DIM], True[DIM], sum[DIM];

void Read()
{
    int i, j;
    scanf("%d%d%d%d", &n, &m, &r, &c);
    for(i = 1; i <= n; ++i)
        for(j = 1; j <= m; ++j)
            scanf("%d", &Aux[i][j]);

    if( n <= m )
        for(i = 1; i <= n; ++i)
            for(j = 1; j <= m; ++j)
                A[i][j] = Aux[i][j];
    else
    {
        int i1, j1;
        for(j = m, i1 = 1; j > 0; --j, ++i1)
            for(i = 1, j1 = 1; i <= n; ++i, ++j1)
                A[i1][j1] = Aux[i][j];
        swap(n, m);
        swap(r, c);
    }
}

void Solve()
{
    int i, j;
    //printf("*");
    for(j = 1; j <= m; ++j)
    {
        sum[j] = 0;
        for(i = 1; i <= n; ++i)
            if( !True[i] )
                sum[j] += A[i][j];
    }
    sort(sum + 1, sum + m + 1);
    int total = 0;
    for(i = m; i > c; --i)
        total += sum[i];

    ans = max(ans, total);
}

void Gen(int nr)
{
    if( nr == r + 1 )
        Solve();
    else
    {
        for(int i = V[nr - 1] + 1; i + r - nr <= n ; ++i)
        {
            V[nr] = i;
            True[i] = 1;
            Gen(nr + 1);
            True[i] = 0;
        }
    }
}

int main()
{
    Read();
    Gen(1);
    printf("%d", ans);
    return 0;
}
