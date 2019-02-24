#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;
FILE *f=freopen("nrdiv.in","r",stdin);
FILE *g=freopen("nrdiv.out","w",stdout);
long long n,nrp=1;
long long int v[101],maxim,w[10001],nr,l;
vector<int>viz(10000001,true);
int main()
{
    long long int i,j;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&v[i]);
        if(v[i]>maxim)
            maxim=v[i];
    }
    maxim=sqrt((double)maxim);
    w[1]=2;
    for(i=3;i*i<=maxim;i+=2)
        if(viz[i]==true)
        {
            w[++nrp]=i;
            for(j=i*i;j<=maxim;j+=2*i)
                viz[j]=false;
        }
    for(i=1;i<=nrp;i++)
        printf("%d ",w[i]);
    for(i=1;i<=n;i++)
    {
        nr=1;
        for(j=1;j<=nrp;j++)
        {
            l=0;
            while(v[i]%w[j]==0)
            {
                ++l;
                v[i]/=w[j];
            }
            nr*=(l+1);
        }
        if(v[i]>1)
            nr*=2;
        printf("%d\n",nr);
    }
    return 0;
}
