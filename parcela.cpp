#include <cstdio>
#include <algorithm>
#define DIM 252
#define MaxS 40040
using namespace std;
FILE *fin=freopen("parcela.in","r",stdin);
FILE *fout=freopen("parcela.out","w",stdout);

const int dx[] = {-1,-1,-1, 1, 1, 1, 0, 0};
const int dy[] = {-1, 0, 1, 0,-1, 1,-1, 1};

int A[DIM][DIM], Nr[DIM * DIM];
int m, n, s, k, val;
bool S[MaxS];

void Read()
{
    int i, j;
    scanf("%d %d %d ", &m, &n, &s);
    for(i = 1; i <= m; ++i)
        for(j = 1; j <= n; ++j)
            scanf("%d", &A[i][j]);
}

void Fill(int x, int y)
{
    ++Nr[k];
    A[x][y] = k + 1;

    int X, Y;
    for(int i = 0; i < 8; ++i)
    {
        X = x + dx[i], Y = y + dy[i];
        if( X > 0 && X <= m && Y > 0 && Y <= n && A[X][Y] == 1 )
            Fill(X, Y);
    }
}

void Solve()
{
    int i, j;
    for(i = 1; i <= m; ++i)
        for(j = 1; j <= n; ++j)
            if( A[i][j] == 1 )
            {
                ++k;
                Fill(i, j);
            }

    int summax = 0;
    S[0] = 1;

    for(j = 1; j <= k; ++j)
    {
        for(i = min(summax, s - Nr[j]); i >= 0; --i )
            if( S[i] )
                S[i + Nr[j]] = 1;
        summax = max( summax, min(summax, s - Nr[j]) + Nr[j] );
    }
    for(i = s; i >= 0; --i)
        if( S[i] )
        {
            printf("%d", i);
            return;
        }
}

int main()
{
    Read();
    Solve();
    return 0;
}
