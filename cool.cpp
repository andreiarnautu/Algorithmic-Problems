#include <cstdio>
using namespace std;
FILE *fin=freopen("cool.in","r",stdin);
FILE *fout=freopen("cool.out","w",stdout);
int N, V[5001], f[1001], K;
void Solve1()
{
    bool ok=1;
    int Min, Max;
    Min=V[1];
    Max=V[1];
    f[V[1]]=1;
    for(int i=2; i<=K ; ++i)
    {
        if(f[V[i]])
            ok=0;
        ++f[V[i]];
        if(Min>V[i])
            Min=V[i];
        if(Max<V[i])
            Max=V[i];
    }
    if(Max-Min+1!=K)
        ok=0;
    if(ok)
        printf("%d",Max);
    else
    {
        int Sol=0;
        for(int i=Min; i<=Max; ++i)
            if(f[i]==1)
                ++Sol;
        printf("%d",Sol);
    }

}
void Solve2()
{
    int Min, Max, Lmax=0, Nr=0;
    for(int i=1; i<N ; ++i)
    {
        Min=V[i];
        Max=V[i];
        f[V[i]]=1;
        for(int j=i+1; j<=N ; ++j)
        {
            if(f[V[j]])
                break;
            f[V[j]]=1;
            if(V[j]>Max)
                Max=V[j];
            if(V[j]<Min)
                Min=V[j];
            if( j-i+1 == Max-Min+1 )
            {
                if( j-i+1 > Lmax)
                {
                    Lmax=j-i+1;
                    Nr=1;
                }
                else if( j-i+1 == Lmax )
                    ++Nr;
            }
        }
        for(int i=Min; i<=Max ; ++i)
            f[i]=0;
    }
    printf("%d\n%d",Lmax,Nr);
}
void Read()
{
    int x;
    scanf("%d%d%d",&x,&N,&K);
    for(int i=1; i<=N ; ++i)
        scanf("%d",&V[i]);
    if(x==1)
        Solve1();
    else
        Solve2();
}
int main()
{
    Read();
    return 0;
}
