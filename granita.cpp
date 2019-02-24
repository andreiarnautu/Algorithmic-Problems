#include <cstdio>
#include <algorithm>

using namespace std;

FILE *fin=freopen("granita.in","r",stdin);
FILE *fout=freopen("granita.out","w",stdout);

int N, p = 1, cnt, limit;
struct two{int a, b;} V[1 << 14];


inline int cmp(two x, two y)
{
    return ( x.a < y.a );
}

int main()
{
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
        scanf("%d%d", &V[i].a, &V[i].b );
    sort( V + 1 , V + N + 1 , cmp );

    while( p < N )
    {
        limit = V[p].b;
        while( V[p + 1].b < limit && p + 1 <= N )
        {
            ++cnt;
            ++p;
        }
        ++p;
    }

    printf("%d",cnt);
}
