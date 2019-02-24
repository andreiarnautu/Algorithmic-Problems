// How about a coding trick?
#include <cstdio>
#include <algorithm>
#define DIM 1515
using namespace std;
FILE *fin=freopen("logs.in","r",stdin);
FILE *fout=freopen("logs.out","w",stdout);

int ind[DIM], val[DIM], ind2[DIM], val2[DIM];
int n, m;
char S[DIM * 10];

void Set()
{
    scanf("%d %d ", &n, &m);
    for(int i = 0; i < m; ++i)
        ind[i] = i;
}

void Solve()
{
    int i, j, st, dr, ans = 0, nr;
    for(i = 1; i <= n; ++i)
    {
        gets(S);
        st = 0, dr = m - 1;
        for(j = m - 1; j >= 0; --j)
        {
            if( S[ind[j]] == '1' )
            {
                ind2[dr] = ind[j];
                val2[dr] = val[j] + 1;
                --dr;
            }
            else
            {
                ind2[st] = ind[j];
                val2[st] = 0;
                ++st;
            }
        }

        for(j = m - 1, nr = DIM * 10; j >= 0; --j)
        {
            nr = min(nr, val2[j]);
            ans = max(ans, nr * (m - j));
        }

        for(j = 0; j < m; ++j)
            val[j] = val2[j], ind[j] = ind2[j];
    }
    printf("%d", ans);
}

int main()
{
    Set();
    Solve();
    return 0;
}
