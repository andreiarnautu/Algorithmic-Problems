// How about a coding trick?
#include <cstdio>
#include <algorithm>
#define DIM 100100
#define MOD 9917
using namespace std;
FILE *fin=freopen("inv.in","r",stdin);
FILE *fout=freopen("inv.out","w",stdout);

int AIB[DIM], nr = 1;
long long int V[DIM], Sol[DIM], A[DIM];
int n;

inline int zeros(int x)
{
    return ((x ^ (x - 1)) & x);
}

inline void Add(int pos)
{
    for(int i = pos; i <= nr; i += zeros(i))
        ++AIB[i];
}

inline int Query(int pos)
{
    int ret = 0;
    for(int i = pos; i > 0; i -= zeros(i))
        ret += AIB[i];
    return ret;
}

void Read()
{
    int i;
    scanf("%d", &n);
    for(i = 1; i <= n; ++i)
        scanf("%lld", &V[i]);
    for(i = 1; i <= n; ++i)
        A[i] = V[i];
}

inline int binary(int val)
{
    int st = 1, dr = nr, m;
    while(st <= dr)
    {
        m = (st + dr) / 2;
        if( val == Sol[m] )
            return m;
        else if( val > Sol[m] )
            st = m + 1;
        else
            dr = m - 1;
    }
}

void Set()
{
    sort(V + 1, V + n + 1);
    Sol[1] = V[1];
    for(int i = 2; i <= n; ++i)
        if( V[i] != V[i - 1] )
            Sol[++nr] = V[i];
    int pos;
    for(int i = 1; i <= n; ++i)
    {
        pos = binary(A[i]);
        A[i] = pos;
    }
}

void Solve()
{
    long long int ansCount = 0;
    for(int i = 1; i <= n; ++i)
    {
        ansCount += 1LL * (i - 1 - Query(A[i]));
        ansCount %= MOD;
        Add(A[i]);
    }
    printf("%lld", ansCount);
}

int main()
{
    Read();
    Set();
    Solve();
    return 0;
}
