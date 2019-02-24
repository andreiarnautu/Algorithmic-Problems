#include <cstdio>
#include <algorithm>
#define DIM 3003
using namespace std;
FILE *fin=freopen("agitatie.in","r",stdin);
FILE *fout=freopen("agitatie.out","w",stdout);

int D1[DIM], D2[DIM];
int St[DIM], Semn[DIM];
int n, tmax;

void Read()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
    {
        scanf("%d %d", &St[i], &Semn[i]);
        if( Semn[i] == -1 )
            tmax = max( tmax, St[i] );
    }
}

inline int Time(int x, int y)
{
    if( Semn[x] == 1 )
        return St[x] + y;
    if( y <= St[x] )
        return St[x] - y;
    return y - St[x];

}

void Solve()
{
    int i, j;
    for(i = n ; i > 0; --i)
        D1[i] = D1[ i + 1 ] + Time(i, tmax);

    for(j = tmax - 1; j >= 0; --j)
    {
        for(i = n; i > 0; --i)
            D2[i] = min( D2[i + 1] + Time(i, j) , D1[i] );
        for(i = n; i > 0; --i)
            D1[i] = D2[i];
    }
    printf("%d", D1[1]);
}

int main()
{
    Read();
    Solve();
    return 0;
}
