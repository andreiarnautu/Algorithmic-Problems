/*
    How about a coding trick?
*/
#include <cstdio>
#include <bitset>
#define DIM 202
using namespace std;
FILE *fin=freopen("cub2.in","r",stdin);
FILE *fout=freopen("cub2.out","w",stdout);

int n, v;
int M[DIM][DIM];
bitset < DIM * DIM * DIM > viz;

void Solve_1()
{
    int Z;
    Z = 1 + v / (n * n);
    if( v % (n * n) == 0 )
        --Z;

    int li = 1, ci = 1, lf = n, cf = n, pas, val, k = n * n, i;

    if( Z % 2 == 0 )
        pas = -1, val = n * n * Z;
    else
        pas = 1, val = n * n * (Z - 1) + 1;

    while( k > 0 )
    {
        for(i = ci; i <= cf; ++i)
            M[li][i] = val, val += pas, --k;
        ++li;

        for(i = li; i <= lf; ++i)
            M[i][cf] = val, val += pas, --k;
        --cf;

        for(i = cf; i >= ci; --i)
            M[lf][i] = val, val += pas, --k;
        --lf;

        for(i = lf; i >= li; --i)
            M[i][ci] = val, val += pas, --k;
        ++ci;
    }

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            if( v == M[i][j] )
            {
                printf("%d %d %d", i, j, Z);
                return;
            }


}

void Ciur()
{
    int i, j, valmax = n * n * n + 5;

    viz[0] = viz[1] = 1;
    for(i = 4; i <= valmax; i += 2)
        viz[ i ] = 1;

    for(i = 3; i * i <= valmax; i += 2)
        if( viz[i] == 0 )
            for(j = i * i; j <= valmax; j += 2 * i)
                viz[ j ] = 1;

}

inline int Back()
{
    int i, j, ret = 0, val;

    for(i = 1; i <= n; ++i)
    {
        if(i % 2 == 1)
        {
            val = n * n * (i - 1) + 1;
            for(j = val; j < val + n; ++j)
                ret += 1 - (viz[j] == 1);
        }

        else
        {
            val = n * n * i;
            for(j = val; j > val - n; --j)
                ret += 1 - (viz[j] == 1);
        }
    }
    return ret;
}

inline int Right()
{
    int i, j, ret = 0, val;
    for(i = 1; i <= n; ++i)
    {
        if(i % 2 == 1)
        {
            val = n * n * (i - 1) + n;
            for(j = val; j < val + n; ++j)
                ret += 1 - (viz[j] == 1);
        }

        else
        {
            val = n * n * i - 2 * (n - 1);
            for(j = val; j < val + n; ++j)
                ret += 1 - (viz[j] == 1);
        }
    }
    return ret;
}

inline int Front()
{
    int i, j, ret = 0, val;
    for(i = 1; i <= n; ++i)
    {
        if(i % 2 == 1)
        {
            val = 1 + n * n * (i - 1) + 2 * (n - 1);
            for(j = val; j < val + n; ++j)
                ret += 1 - (viz[j] == 1);
        }
        else
        {
            val = n * n * i - 3 * (n - 1);
            for(j = val; j < val + n; ++j)
                ret += 1 - (viz[j] == 1);
        }
    }
    return ret;
}

inline int Left()
{
    int i, j, ret = 0, val;
    for(i = 1; i <= n; ++i)
    {
        if(i % 2 == 1)
        {
            val = n * n * (i - 1) + 1;
            ret += 1 - (viz[val] == 1);
            val += 3 * (n - 1);
            for(j = val; j < val + n - 1; ++j)
                ret += 1 - (viz[j] == 1);
        }
        else
        {
            val = n * n * i;
            ret += 1 - (viz[val] == 1);
            val -= 4 * (n - 1);
            ++val;
            for(j = val; j < val + n - 1; ++j)
                ret += 1 - (viz[j] == 1);
        }
    }
    return ret;
}

void Solve_2()
{
    Ciur();
    int a, b, c, d;
    a = Back();
    b = Right();
    c = Front();
    d = Left();
    printf("%d\n%d\n%d\n%d\n", a, b, c, d);
}

int main()
{
    int op;
    scanf("%d %d %d", &op, &n, &v);
    if( op == 1 )
        Solve_1();
    else
        Solve_2();
    return 0;
}
