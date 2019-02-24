#include <cstdio>
using namespace std;
FILE *fin=freopen("defrag.in","r",stdin);
FILE *fout=freopen("defrag.out","w",stdout);

int A[110][369];
int p, s;

void Solve1()
{
    int cnt = 0;
    for(int i = 1; i <= p; ++i)
        if( !A[i][0] )
            ++cnt;
    printf("%d\n", cnt);
}

void Solve2()
{
    int terms, i, j, best;

    for(i = 1; i <= p; ++i)
    {
        best = A[i][0], terms = 0;

        for(j = 1; j <= 1 + A[i][0] - 1; ++j)
            terms += A[i][j];

        best = A[i][0] - terms;

        for(j = 1; j <= s; ++j)
        {
            terms -= A[i][j];
            if( j + A[i][0] <= s )
            {
                terms += A[i][j + A[i][0]];
            }
            else
                terms += A[i][j + A[i][0] - s];

            if( best > A[i][0] - terms )
                best = A[i][0] - terms;
        }
        printf("%d ", best);
    }
}

void Read()
{
    int op, c;
    scanf("%d %d %d %d", &op, &p, &s, &c);

    int x, y;
    for(int i = 1; i <= c; ++i)
    {
        scanf("%d %d", &x, &y);
        ++A[x][0];
        A[x][y] = 1;
    }

    if( op == 1 )
        Solve1();
    else
        Solve2();
}

int main()
{
    Read();
    return 0;
}
