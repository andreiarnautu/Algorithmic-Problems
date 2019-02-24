#include <cstdio>
using namespace std;
FILE *fin=freopen("livada.in","r",stdin);
FILE *fout=freopen("livada.out","w",stdout);
int M, N, X, Max;
int V[22600];

void Read()
{
    scanf("%d%d%d", &N, &M, &X);
    N *= M;
    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%d", &V[i]);
        if( V[i] > Max )
            Max = V[i];
    }
}

void Solve()
{
    int st, dr, t, m;
    dr = Max;
    st = 0;
    if(X == 1)
    {
        printf("%d", dr);
        return;
    }
    while( st + 1 < dr )
    {
        m = (st + dr) / 2;
        t = 0;
        for(int i = 1 ; i <= N ; ++i )
            if( V[i] > m )
                t += ( V[i] - m + X - 2) / (X - 1);
     //   printf("%d %d\n",m,t);
        if( t <= m )
            dr = m;
        else
            st = m;
    }
    printf("%d",dr);
}

int main()
{
    Read();
    Solve();
    return 0;
}
