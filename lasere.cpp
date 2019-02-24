// It's not the load that breaks you down, it's the way you carry it.

#include <cstdio>
#include <cstring>
#define DIM 220
using namespace std;
FILE *fin=freopen("lasere.in","r",stdin);
FILE *fout=freopen("lasere.out","w",stdout);

const int dx[] = {-1,-1,-1, 0, 0, 1, 1, 1};
const int dy[] = {-1, 0, 1,-1, 1,-1, 0, 1};

int A[DIM][DIM], op;
bool G[DIM][DIM];
int n, m;

void Solve2()
{
    int i, j, len, groupsCount = 0;

    for(i = 1; i <= n; ++i)
    {
        len = 0;
        for(j = 1; j <= n; ++j)
        {
            if( !G[i][j] )
                len = 0;
            else
                ++len;
            if( len == 2 )
                ++groupsCount;
        }
    }
    printf("%d\n", groupsCount);
}

void Solve1()
{
    int i, j, l, holesCount = 0, x, y;
    int ok;

    for(i = 1; i <= n; ++i)
        for(j = 1; j <= n; ++j)
        {
            ok = 1;
            for(l = 0; l < 8; ++l)
            {
                x = i + dx[l], y = j + dy[l];
                if( A[i][j] > A[x][y] )
                    ok = 0;
            }
            G[i][j] = ok;

            if( ok )
                ++holesCount;
        }

    if( op == 1 )
        printf("%d\n", holesCount);
    else
        Solve2();
}

void Read()
{
    int i, j, l, x, y, d;
    scanf("%d %d %d", &op, &n, &m);

    memset(A, 1000000, sizeof(A));

    for(i = 1; i <= n; ++i)
        for(j = 1; j <= n; ++j)
            scanf("%d", &A[i][j]);

    for(l = 1; l <= m; ++l)
    {
        scanf("%d %d %d", &x, &y, &d);
        if( d == 1 )
            for(i = x - 1; i > 0; --i)
                --A[i][y];

        else if( d == 2 )
            for(j = y + 1; j <= n; ++j)
                --A[x][j];

        else if( d == 3 )
            for(i = x + 1; i <= n; ++i)
                --A[i][y];

        else
            for(j = y - 1; j > 0; --j)
                --A[x][j];
    }

    Solve1();
}

int main()
{
    Read();
    return 0;
}
