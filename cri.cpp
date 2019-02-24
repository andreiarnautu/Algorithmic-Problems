#include <cstdio>
#define DIM 505
using namespace std;
FILE *fin=freopen("cri.in","r",stdin);
FILE *fout=freopen("cri.out","w",stdout);

int A[DIM][DIM];
int m, n, x, y, foodCount, len;

void Read()
{
    scanf("%d %d %d %d ", &n, &m, &x, &y);
    int i, j;

    for(i = 1; i <= n; ++i)
        for(j = 1; j <= m; ++j)
            scanf("%d ", &A[i][j]);
}

void Zone1()
{
    int nl = 0, nc = 0, MIN = 8003, i, j;
    foodCount = 0;

    for(i = x; i > 0; --i)
    {
        ++nl, nc = 0;
        for(j = y; j > 0; --j)
        {
            ++nc;
            foodCount += A[i][j];

            if( MIN > A[i][j] && (nl + nc) % 2 == 1 )
                MIN = A[i][j];
        }
    }
    len = nl * nc;

    if( nl % 2 == 0 && nc % 2 == 0 )
    {
        --len;
        foodCount -= MIN;
    }

}

void Zone2()
{
    int nl = 0, nc, i, j, MIN = 8003;
    foodCount = 0;

    for(i = x; i > 0; --i)
    {
        ++nl, nc = 0;
        for(j = y; j <= m; ++j)
        {
            ++nc;
            foodCount += A[i][j];
            if( MIN > A[i][j] && (nl + nc) % 2 == 1 )
                MIN = A[i][j];
        }
    }

    len = nl * nc;
    if( nl % 2 == 0 && nc % 2 == 0 )
    {
        --len;
        foodCount -= MIN;
    }
}

void Zone3()
{
    int MIN = 8003, i, j, nl = 0, nc;
    foodCount = 0;

    for(i = x; i <= n; ++i)
    {
        ++nl, nc = 0;
        for(j = y; j > 0; --j)
        {
            ++nc;
            foodCount += A[i][j];
            if( MIN > A[i][j] && (nl + nc) % 2 == 1 )
                MIN = A[i][j];
        }
    }

    len = nl * nc;
    if( nl % 2 == 0 && nc % 2 == 0 )
    {
        --len, foodCount -= MIN;
    }
}

void Zone4()
{
    int MIN = 8003, nl = 0, nc, i, j;
    foodCount = 0;

    for(i = x; i <= n; ++i)
    {
        ++nl, nc = 0;
        for(j = y; j <= m; ++j)
        {
            ++nc;
            foodCount += A[i][j];
            if( MIN > A[i][j] && (nl + nc) % 2 == 1 )
                MIN = A[i][j];
        }
    }

    len = nl * nc;

    if( nl % 2 == 0 && nc % 2 == 0 )
    {
        foodCount -= MIN, len--;
    }
}

void Solve()
{
    int best = -1, nr, k;

    Zone1();
    if( best < foodCount )
    {
        best = foodCount, nr = len, k = 1;
    }
    else if( best == foodCount && nr > len )
    {
        nr = len, k = 1;
    }

    Zone2();
    if( best < foodCount )
    {
        best = foodCount, nr = len, k = 2;
    }
    else if( best == foodCount && nr > len )
    {
        nr = len, k = 2;
    }

    Zone3();
    if( best < foodCount )
    {
        best = foodCount, nr = len, k = 3;
    }
    else if( best == foodCount && nr > len )
    {
        nr = len, k = 3;
    }

    Zone4();
    if( best < foodCount )
    {
        best = foodCount, nr = len, k = 4;
    }
    else if( best == foodCount && nr > len )
    {
        nr = len, k = 4;
    }

    printf("%d %d %d ", k, best, nr);
}

int main()
{
    Read();
    Solve();
    return 0;
}
