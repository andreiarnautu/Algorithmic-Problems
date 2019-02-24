#include <cstdio>
using namespace std;
FILE *fin=freopen("joker.in","r",stdin);
FILE *fout=freopen("joker.out","w",stdout);
long V[100001], S[100001], N, K, Max;

void Solve()
{
    ++Max;
    for(int i=1; i <= N+2 ; ++i)
    {
        if( S[i-1] > 0 && V[i] > 0 )
        {
            S[i] = S[i-1] + 1;
            if( S[i] > Max )
                Max = S[i];
        }
        else if ( V[i-1] == 0 && V[i-2] > 0 && V[i]>0)
        {
            S[i] = V[i-2] + 2;
            if( S[i] > Max)
                Max = S[i];
        }
    }
    printf("%d",Max);
}

void Read()
{
    int x;
    bool ok=0;
    scanf("%d%d",&N,&K);
    for(int i=0; i<K ; ++i)
    {
        scanf("%d",&x);
        if( x == 0 )
            ok = 1 ;
        else
        {
            V[x] = V[x-1] + 1;
            if( V[x] > Max )
                Max = V[x];
        }
    }
    for(int i=1; i<=N+1 ; ++i)
    {
        if( V[i-1] > 0 && V[i] < V[i-1] +1 && V[i]>0)
        {
            V[i] = V[i-1] +1;
            if( V[i] > Max )
                Max = V[i];
        }
    }
    if( !ok )
    {
        printf("%d", Max);
        return;
    }
    Solve();
}

int main()
{
    Read();
    return 0;
}
