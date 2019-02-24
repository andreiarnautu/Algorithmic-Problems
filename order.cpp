/*
    How about a coding trick?
*/
#include <cstdio>
#define zeros(x) ((x ^ (x - 1)) & x)
#define DIM 30030
using namespace std;
FILE *fin=freopen("order.in","r",stdin);
FILE *fout=freopen("order.out","w",stdout);

int AIB[DIM];
int n;

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

int main()
{
    int i, p2;
    scanf("%d", &n);
    for(p2 = 1; p2 < n; p2 <<= 1);

    for(i = 1; i <= n; ++i)
        Add(i, 1);

    int needed, nr, pos = 1, j;
    for(i = 1; i <= n; ++i)
    {
        needed = i % (n - i + 1);
        if( !needed )
            needed = n - i + 1;

        nr = Query(n) - Query(pos);
        if( needed <= nr )
            nr = Query(pos) + needed;
        else
            nr = needed - nr;

        pos = 0;
        for(j = p2; j; j >>= 1)
            if(j + pos < n && Query(j + pos) < nr)
                pos += j;
        ++pos;
        printf("%d ", pos);
        Add(pos, -1);
    }
    return 0;
}
