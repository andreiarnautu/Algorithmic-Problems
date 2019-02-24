/*
    Worg
*/
#include <bitset>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define DIM 100100
#define zeros(x) ((x ^ (x - 1)) & x)

using namespace std;
FILE *fin=freopen("mess.in","r",stdin);
FILE *fout=freopen("mess.out","w",stdout);

char buff[DIM];
int pos;
int n, m;
int v[DIM], AIB[DIM], a[DIM];
bitset < DIM > stare;

inline int read()
{
    int ret = 0;
    while( buff[pos] < '0' || buff[pos] > '9' )
        if( ++pos == DIM )
        {
            fread(buff, 1, DIM, fin); pos = 0;
        }

    while( buff[pos] >= '0' && buff[pos] <= '9' )
    {
        ret = ret * 10 + buff[pos] - '0';
        if( ++pos == DIM )
        {
            fread(buff, 1, DIM, fin); pos = 0;
        }
    }
    return ret;
}

inline void Add(int pos, int val)
{
    int i;
    for(i = pos; i <= n; i += zeros(i))
        AIB[i] += val;
}

inline int Query(int pos)
{
    int i, ret = 0;
    for(i = pos; i; i -= zeros(i))
        ret += AIB[i];
    return ret;
}

inline int b_search(int val)
{
    int st = 1, dr = n, m, sol;
    while( st <= dr )
    {
        m = (st + dr) >> 1;
        if( v[m] >= val )
            sol = m, dr = m - 1;
        else
            st = m + 1;
    }
    return sol;
}

void Set()
{
    fread(buff, 1, DIM, fin);
    n = read();
    m = read();
    for(int i = 1; i <= n; ++i)
        a[i] = v[i] = read(), stare[i] = 1;
    sort(v + 1, v + n + 1);
}

void Solve()
{
    int i, op, val, x, diff, p, q, k;
    for(i = 1; i <= m; ++i)
    {
        op = read();
        if( op == 1 )
        {
            val = read();
            val = a[ val ];
            x = b_search(val);
            stare[x] = 1 - stare[x];
            if( stare[x] == 0 )
                diff = -1;
            else
                diff = 1;
            Add(x, 1);
        }
        else
        {
            p = read(), q = read(), k = read();

        }
    }
}

int main()
{
    Set();
    Solve();
    return 0;
}
