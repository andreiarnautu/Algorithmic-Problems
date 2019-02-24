#include <cstdio>
#define min(a,b) a > b ? b : a
#define MaxN 100013
#define lli long long int
using namespace std;

FILE *fin = freopen("grupuri.in","r",stdin);
FILE *fout = freopen("grupuri.out","w",stdout);

lli n, k, nr;
lli A[MaxN];


void Read()
{
    scanf("%lld%lld", &k, &n);
    for(lli i = 1; i <= n ; ++i)
    {
        scanf("%lld", &A[i]);
        nr += A[i];
    }
}

inline bool Check(lli m)
{
    lli s = 0;
    for(lli i = 1; i <= n ; ++i)
        s += min( A[i], m );
    if( s >= m * k )
        return 1;
    return 0;
}

void Solve()
{
    lli left = 0, right = nr / k + 1, m, sol = -1;

    while( left <= right )
    {
        m = (left + right) >> 1;
        if( Check(m) )
        {
            if(sol < m)
                sol = m;
            left = m + 1;
        }
        else
            right = m - 1;
    }
    printf("%lld", sol);
}

int main()
{
    Read();
    Solve();
    return 0;
}
