#include <cstdio>
using namespace std;
FILE *fin=freopen("case.in","r",stdin);
FILE *fout=freopen("case.out","w",stdout);
int N, V[10001];

void Read()
{
    int Nr = 0;
    scanf("%d",&N);
    for(int i=1; i<=N ; ++i)
    {
        scanf("%d",&V[i]);
        if( i == V[i] )
            ++Nr;
    }
    printf("%d\n",Nr);
}

void Solve()
{
    int Max = 0, I, Imax = 0, j, steps, nr;
    for(int i=1; i<=N ; ++i)
    {
        j = i;
        steps = 1;
        I = 0;
        while( V[j] != i )
        {
            ++steps;
            if( V[j] > V[V[j]] )
                ++I;
            j = V[j];
        }
        if( Max < steps )
        {
            Max = steps;
            Imax = I;
            nr = i;
        }
        else if( Max == steps && Imax < I )
        {
            Imax = I;
            nr = i;
        }
    }
    printf("%d\n%d\n",Max,nr);
}

int main()
{
    Read();
    Solve();
    return 0;
}
