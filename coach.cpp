// How about a coding trick?
#include <cstdio>
#include <algorithm>
#define DIM 110
#define INF 1000000000
using namespace std;
FILE *fin=freopen("coach.in","r",stdin);
FILE *fout=freopen("coach.out","w",stdout);

struct type{
                int ind, val;
           };
type V[DIM];

int A[DIM][DIM], Init[DIM][DIM], Pos[DIM];
int n, m, t;
int nod1, nod2, cmin, cmax;

inline bool comp(type a, type b)
{
    return a.val < b.val;
}

void Read()
{
    scanf("%d %d %d", &n, &m, &t);
    int i, j, x, y, cost;
    for(i = 1; i <= n; ++i)
        for(j = 1; j <= n; ++j)
            Init[i][j] = INF;
    for(i = 1; i <= n; ++i)
    {
        scanf("%d", &V[i].val);
        V[i].ind = i;
    }
    sort(V + 1, V + n + 1, comp);
    for(i = 1; i <= n; ++i)
        Pos[V[i].ind] = i;

    for(i = 1; i <= m; ++i)
    {
        scanf("%d %d %d", &x, &y, &cost);
        Init[Pos[x]][Pos[y]] = Init[Pos[y]][Pos[x]] = cost;
    }
}

inline int Check(int first)
{
    int i, j, l;
    for(i = 1; i < first; ++i)
        for(j = 1; j < first; ++j)
            A[i][j] = INF;
    for(i = first; i <= n; ++i)
        for(j = first; j <= n; ++j)
            A[i][j] = Init[i][j];

    for(l = first; l <= n; ++l)
    {
        for(i = first; i <= n; ++i)
            for(j = first; j <= n; ++j)
                if( A[i][l] != INF && A[l][j] != INF && A[i][j] > A[i][l] + A[l][j])
                    A[i][j] = A[i][l] + A[l][j];

        for(i = first; i <= l; ++i)
            for(j = first; j <= l; ++j)
                if( A[i][j] == t )
                {
                    nod1 = V[i].ind, nod2 = V[j].ind;
                    cmin = V[first].val, cmax = V[l].val;
                    return 1;
                }
    }
    return 0;
}

void Solve()
{
    int i;
    for(i = 1; i <= n; ++i)
        if( Check(i) )
            break;
    printf("%d %d %d %d", nod1, nod2, cmin, cmax);
}

int main()
{
    Read();
    Solve();
    return 0;
}
