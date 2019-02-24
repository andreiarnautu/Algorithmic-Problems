#include <cstdio>
#include <vector>
using namespace std;
FILE *fin=freopen("factori.in","r",stdin);
FILE *fout=freopen("factori.out","w",stdout);
vector<bool>ciur(66000,true);
int w[40000],p=1,f[6900];
void rezolva(int n)
{
    int i,ii,k=0,pr;
    for(i=0;i<=p;i++)
        f[i]=0;
    for(i=0;i<p;i++)
    {
        pr=w[i];
        while(pr<=n)
        {
            f[i]+=n/pr;
            pr*=w[i];
        }
    }
    for(i=0;i<p;i++)
        if(f[i]!=0)
            printf("%d ",f[i]);
    printf("\n");
}
int main()
{
    long long i,j,n;
    w[0]=2;
    for(i=3;i<60000;i+=2)
        if(ciur[i]==true)
        {
            w[p]=i;
            ++p;
            for(j=i;i*j<60000;j+=2)
                ciur[i*j]=false;
        }
    scanf("%d",&n);
    while(n!=60001)
    {
        if(n>2)
            rezolva(n);
        n=60001;
        scanf("%d",&n);
    }
    return 0;
}
