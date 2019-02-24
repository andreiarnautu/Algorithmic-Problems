#include <cstdio>
#include <vector>
using namespace std;
FILE *fin=freopen("paisprezece.in","r",stdin);
FILE *fout=freopen("paisprezece.out","w",stdout);
int P[]={2,3,5,7,11,13,17,19};
vector<bool>viz(1000005);
long long a,b;
void Read()
{
    scanf("%lld%lld",&a,&b);
}
void Ciur()
{
    for(long i=3; i*i<=1000000 ; i+=2)
        if(viz[i]==false)
            for(long j=i*i; j<=1000000 ; j+=2*i)
                viz[j]=1;
    viz[0]=1;
    viz[1]=1;
}
long long putere(int x)
{
    long long y=1;
    for(int i=0 ; i<6 ; ++i)
        y*=x;
    return y;
}
int cerinta(long long x, long long y)
{
    if(x>2 && x%2==0)
        return 0;
    if(viz[x])
        return 0;
    if(x==y)
        return 0;
    return 1;
}
void Solve()
{
    long long x,nr=0,r1,r2;
    if(8192>=a && 8192<=b)
        ++nr;
    if(1594323>=a && 1594323<=b)
        ++nr;
    for(int i=0; i<=7 ; ++i)
    {
        x=putere(P[i]);
        if(x>b)
            break;
        if(a%x==0)
            r1=a/x;
        else
            r1=a/x+1;
        r2=b/x;
        for(long j=r1; j<=r2 ; ++j)
            if(cerinta(j,P[i]))
                ++nr;
    }
    printf("%d",nr);
}
int main()
{
    Read();
    Ciur();
    Solve();
    return 0;
}
