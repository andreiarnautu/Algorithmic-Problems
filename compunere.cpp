#include <cstdio>
#include <algorithm>
#define DIM 100010
#define INF 2000000000
using namespace std;
FILE *fin=freopen("compunere.in","r",stdin);
FILE *fout=freopen("compunere.out","w",stdout);

int m, n, ret;
int B[DIM];
struct vec{int val, ord;} A[DIM], C[DIM];

void Read()
{
    scanf("%d %d ", &m, &n);
    if( m < n )
    {
        swap(m , n);
        for(int i = 1; i <= n; ++i)
        {
            scanf("%d", &B[i]);
        }
        for(int i = 1; i <= m; ++i)
        {
            scanf("%d", &A[i].val);
            A[i].ord = i;
        }
    }

    else
    {
        for(int i = 1; i <= m; ++i)
        {
            scanf("%d", &A[i].val);
            A[i].ord = i;
        }

        for(int i = 1; i <= n; ++i)
            scanf("%d", &B[i]);
    }
}

inline bool comp(vec p, vec q)
{
    return( p.val < q.val );
}

inline int binar(int nr)
{
    int st = 1, dr = m, mid, sol = INF;
    ret = -1;

    while( st <= dr )
    {
        mid = (st + dr) / 2;

        if( A[mid].val == nr )
        {
            sol = A[mid].ord;
            ret = A[mid].val;
            return sol;
        }

        else if( A[mid].val < nr )
        {
            st = mid + 1;
        }
        else
            dr = mid - 1;
    }

    return sol;
}

void Solve()
{
    sort(A + 1, A + m + 1, comp);

    for(int i = 1; i <= m; ++i)
        printf("%d %d\n", A[i].val, A[i].ord);

    int i, j;

    int P;

    for(i = 1; i <= n; ++i)
    {
        P = binar( B[i] );
        C[i].ord = P;
        C[i].ord = ret;
        printf("%d ", C[i].ord);
    }


}

int main()
{
    Read();
    Solve();
    return 0;
}
