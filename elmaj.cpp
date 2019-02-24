#include <cstdio>
#define DIM 1000100
using namespace std;
FILE *fin=freopen("elmaj.in","r",stdin);
FILE *fout=freopen("elmaj.out","w",stdout);

int V[DIM];

int main()
{
    int elem, i, n, cnt = 0;
    scanf("%d", &n);

    for(i = 1; i <= n; ++i)
    {
        scanf("%d", &V[i]);
        if( cnt == 0 )
        {
            ++cnt, elem = V[i];
        }
        else if( elem == V[i] )
            ++cnt;
        else
            --cnt;
    }

    if( !cnt )
    {
        printf("-1");
        return 0;
    }

    cnt = 0;
    for(i = 1; i <= n; ++i)
        if( elem == V[i] )
            ++cnt;
    if( cnt > n / 2 )
        printf("%d %d", elem, cnt);
    else
        printf("-1");
    return 0;
}
