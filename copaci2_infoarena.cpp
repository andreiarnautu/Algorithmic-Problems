#include <cstdio>
#include <deque>
#include <vector>
#include <algorithm>
#define INF 1 << 30
#define DIM 1010
using namespace std;
FILE *fin=freopen("copaci2.in","r",stdin);
FILE *fout=freopen("copaci2.out","w",stdout);

vector < pair <int,int> > V;
deque <int> D;
int A[2][DIM];
int n, k, hmax;

void Read()
{
    int x, y;
    scanf("%d %d ", &n, &k);
    for(int i = 1; i <= n ; ++i)
    {
        scanf("%d %d ", &x, &y);
        V.push_back(make_pair(x, y));
        if( hmax < x )
            hmax = x;
    }
}

inline int ABS(int x)
{
    if( x > 0 )
        return x;
    return -x;
}

inline int Cost(int dist)
{
    int i, j, ct = min(1000, hmax);

    for(i = 0; i <= 1000; ++i)
        A[0][i] = A[1][i] = 0;

    for(i = 1; i <= n; ++i)
    {
        for(j = 0; j < dist; j++)
        {
            while( !D.empty() && A[0][j] < A[0][D.back()] )
                D.pop_back();
            D.push_back( j );
        }
        for(j = 0; j <= ct ; ++j)
        {
            if( j + dist <= ct )
            {
                while( !D.empty() && A[0][j + dist] < A[0][D.back()] )
                    D.pop_back();
                D.push_back( j + dist );
            }
            if( j - D.front() > dist)
                D.pop_front();
            A[1][j] = ABS(V[i - 1].first - j) * V[i - 1].second + A[0][D.front()];
        }
        for(j = 0; j <= ct; ++j)
            A[0][j] = A[1][j];
        D.clear();
    }

    D.clear();

    int best = INF;
    for(i = 1; i <= ct; ++i)
        if( best > A[1][i] && A[1][i] != 0 )
            best = A[1][i];

    return best;
}

void Solve()
{
    int p2, aux = 0, st, dr, m, sol;

    for( p2 = 1; p2 < k; p2 <<= 1);

    st = 0, dr = hmax;

    while( st <= dr )
    {
        m = (st + dr) / 2;
        if( Cost(m) <= k )
        {
            sol = m;
            dr = m - 1;
        }
        else
            st = m + 1;
    }

    printf("%d", sol);
}

int main()
{
    Read();
    Solve();
    return 0;
}
