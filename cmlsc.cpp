#include <cstdio>
#include <vector>
#include <algorithm>
#define FOR(i,a,b) for(i = a; i <= b; ++i)
#define FoR(i,a,b) for(i = a; i >= b; --i)
using namespace std;

FILE *fin=freopen("cmlsc.in","r",stdin);
FILE *fout=freopen("cmlsc.out","w",stdout);

int DP[1 << 10 + 1][1 << 10 + 1];
vector <int> A, B;

int m, n, V[1 << 10 + 1], x;

void Read()
{
    int i, x;

    scanf("%d%d", &m, &n);
    A.reserve(m);
    B.reserve(n);

    FOR(i, 1, m)
    {
        scanf("%d", &x);
        A.push_back(x);
    }

    FOR(i, 1, n)
    {
        scanf("%d", &x);
        B.push_back(x);
    }
}

void Solve()
{
    int i, j;
    FOR(i, 1, m)
    {
        FOR(j, 1, n)
        {
            if(A[i - 1] == B[j - 1])
                DP[i][j] = DP[i - 1][j - 1] + 1;
            else
                DP[i][j] = max( DP[i - 1][j], DP[i][j - 1] );
        }
    }
    printf("%d\n", DP[m][n]);

    for( i = m, j = n; i && j; )
    {
        if( A[i - 1] == B[j - 1] )
            V[++x] = A[i - 1], --i, --j;

        else if( DP[i - 1][j] > DP[i][j - 1] )
            --i;
        else
            --j;
    }

    FoR(i, x, 1)
        printf("%d ", V[i]);

}

int main()
{
    Read();
    Solve();
}
