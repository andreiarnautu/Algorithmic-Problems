#include <cstdio>
#include <algorithm>
#define Nmax 1002
#define Inf 1000000000
using namespace std;
FILE *fin=freopen("fall.in","r",stdin);
FILE *fout=freopen("fall.out","w",stdout);

int x1[Nmax], x2[Nmax], H[Nmax], p[Nmax], st[Nmax], dr[Nmax], N, Hmax;
long mst[Nmax], mdr[Nmax];
char undest[Nmax], undedr[Nmax];

void Read()
{
    int x, y;
    scanf("%d%d%d%d", &N, &x, &y, &Hmax);
    for(int i = 1 ; i <= N ; ++i )
        scanf("%d%d%d", &x1[i], &x2[i], &H[i]);
    x1[0] = x;
    x2[0] = x;
    H[0] = y;
    x1[N + 1] = -30000;
    x2[N + 1] = 30000;
    H[N + 1] = 0;
    N += 2;
}

void Sort()
{
    int i, j, ok;
    for( i = 0 ; i < N ; ++i )
        p[i] = i;
    do
    {
        ok = 0;
        for( i = 2 ; i < N ; ++i )
            if( H[p[i]] > H[p[i-1]] )
            {
                swap(p[i], p[i-1]);
                ok = 1;
            }
    }while(ok);
}

void st_dr()
{
    for(int i = 0 ; i < N ; ++i )
    {
        st[p[i]] = dr[p[i]] = 0;
        for(int j = i + 1 ; H[p[i]] - H[p[j]] <= Hmax && ( !st[p[i]] || !dr[p[i]] ) && j <= N; ++j )
        {
            if( !st[p[i]] && x1[p[j]] <= x1[p[i]] && x1[p[i]] <= x2[p[j]] )
                st[p[i]] = p[j];
            if( !dr[p[j]] && x1[p[j]] <= x2[p[i]] && x2[p[i]] <= x2[p[j]] )
                dr[p[i]] = p[j];
        }
    }
}

void Solve()
{
    int i, j, lgst, lgdr;
    mst[N - 1] = mdr[N - 1] = 0;
    for( j = N - 2 ; j >= 0 ; j-- )
    {
        i = p[j];
        mst[i] = mdr[i] = Inf;
        if( st[i] )
        {
            if( st[i] == N - 1 )
                lgst = lgdr = 1;
            else
            {
                lgst = mst[st[i]] + abs( x1[i] - x1[st[i]] );
                lgdr = mdr[st[i]] + abs( x1[i] - x2[st[i]] );
            }
            if( lgst < lgdr )
            {
                mst[i] = lgst + abs( H[i] - H[st[i]] );
                undest[i] = 'S';
            }
            else
            {
                mst[i] = lgdr + abs(H[i] - H[st[i]]);
                undest[i] = 'D';
            }
        }
        if( dr[i] )
        {
            if( dr[i] == N - 1 )
                lgst = lgdr = 0;
            else
            {
                lgst = mst[dr[i]] + abs( x2[i] - x2[dr[i]] );
                lgdr = mdr[dr[i]] + abs( x2[i] - x2[dr[i]] );
            }
            if( lgst < lgdr )
            {
                mdr[i] = lgst + abs(H[i] - H[dr[i]]);
                undedr[i] = 'S';
            }
            else
            {
                mdr[i] = lgdr + abs(H[i] - H[dr[i]]);
                undedr[i] = 'D';
            }
        }
    }
}

void Output()
{
    printf("%d", mst[0]);
}

int main()
{
    Read();
    Sort();
    st_dr();
    Solve();
    Output();
    return 0;
}
