#include <cstdio>
using namespace std;
FILE *fin=freopen("finala.in","r",stdin);
FILE *fout=freopen("finala.out","w",stdout);
int N, M, K;
void Read()
{
    scanf("%d%d%d",&N,&M,&K);
}
void Solve()
{
    int x;
    x=K-2;
    if(x<=0)
    {
        printf("0");
        return;
    }
    int Bus,r;
    Bus=N/x;
    r=N%x;
    if(r)
        ++Bus;
    int p;
    p=2*Bus;
    if( p==M )
    {
        printf("%d",Bus);
        return;
    }
    if( M<p )
    {
        printf("0");
        return;
    }
    int rp;
    rp=M-p;
    if( r )
    {
        int LastBus;
        LastBus=K-2-r;
        rp-=LastBus;
        Bus+=rp/K;
        if( rp%K )
            ++Bus;
        printf("%d",Bus);
    }
    else
    {
        Bus+=rp/K;
        if( rp%K )
            ++Bus;
        printf("%d",Bus);
    }
}
int main()
{
    Read();
    Solve();
    return 0;
}
