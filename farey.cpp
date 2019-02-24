#include <cstdio>
#include <vector>
#include <algorithm>
#define DIM 40040
using namespace std;
FILE *fin=freopen("farey.in","r",stdin);
FILE *fout=freopen("farey.out","w",stdout);

int n, k, A[DIM];

vector < pair<int,int> > V;

void Read()
{
    scanf("%d %d ", &n, &k);
}

inline int fracCount(int p)
{
    int i, j, ret = 0;

    for(i = 2; i <= n; ++i)
        A[i] = i * p / n;

    for(i = 2; i <= n; ++i)
        for(j = 2 * i; j <= n; j += i)
            A[j] -= A[i];

    for(i = 2; i <= n; ++i)
        ret += A[i];
    return ret;
}

inline int gcd(int a, int b)
{
    int r;
    while( b )
    {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

inline int comp( pair <int,int> x, pair <int,int> y )
{
    return x.first * y.second < x.second * y.first;
}

void Solve()
{
    int val = 1, left, right, m, a, b, cmmdc, rest, i;

    left = 1, right = n;

    while( left <= right )
    {
        m = (left + right) / 2;
        if( fracCount(m) < k )
        {
            val = m + 1;
            left = m + 1;
        }
        else
            right = m - 1;
    }

    rest = k - fracCount(val - 1);

    for(i = 1; i <= n; ++i)
    {
        a = i * (val) / n;
        b = i;
        cmmdc = gcd(a , b); a /= cmmdc, b /= cmmdc;

        if( (double)a / (double) b > (double)(val - 1) / (double) n && (double)a / (double) b <= (double)(val) / (double) n )
        {
            V.push_back(make_pair(a, b));
        }
    }

    sort( V.begin(), V.end(), comp );

    for(i = 0; i < V.size(); ++i)
    {
        if( V[i] != V[i + 1] )
            --rest;
        if( !rest )
        {
            printf("%d %d ", V[i].first, V[i].second);
            break;
        }
    }

}

int main()
{
    Read();
    Solve();
    return 0;
}
