/*
    How about a coding trick?
*/
#include <cstdio>
#include <algorithm>
#define zeros(x) ((x ^ (x - 1)) & x)
#define DIM 3535
using namespace std;
FILE *fin=freopen("cutii.in","r",stdin);
FILE *fout=freopen("cutii.out","w",stdout);

int AIB[DIM][DIM];
struct sizes{
                int x, y, z;
            };
sizes Box[DIM];
int DP[DIM], n;

inline void Update(int x, int y, int val)
{
    int i, j;
    for(i = x; i <= n; i += zeros(i))
        for(j = y; j <= n; j += zeros(j))
            AIB[i][j] = max( AIB[i][j], val );
}

inline int Query(int x, int y)
{
    int ret = 0;
    for(int i = x; i ; i -= zeros(i))
        for(int j = y; j; j -= zeros(j))
            ret = max( ret, AIB[i][j] );
    return ret;
}

inline bool comp(sizes a, sizes b)
{
    return a.x < b.x;
}

inline void Set()
{
    int l, i, j;
    for(l = 1; l <= n; ++l)
    {
        for(i = Box[l].y; i <= n; i += zeros(i))
            for(j = Box[l].z; j <= n; j += zeros(j))
                AIB[i][j] = 0;
    }
}

inline void Solve()
{
    int i;
    for(i = 1; i <= n; ++i)
        scanf("%d %d %d", &Box[i].x, &Box[i].y, &Box[i].z);
    sort( Box + 1, Box + n + 1, comp );
    for(i = 1; i <= n; ++i)
    {
        DP[i] = Query( Box[i].y - 1, Box[i].z - 1 ) + 1;
        Update( Box[i].y, Box[i].z, DP[i] );
    }

    int ans = 0;
    for(i = 1; i <= n; ++i)
        ans = max(ans, DP[i]);
    printf("%d\n", ans);
    Set();
}

int main()
{
    int teste;
    scanf("%d %d", &n, &teste);
    for(; teste; --teste)
        Solve();
    return 0;
}
