#include <cstdio>
using namespace std;
FILE *fin=freopen("butoane.in","r",stdin);
FILE *fout=freopen("butoane.out","w",stdout);
int n;
long long x[1001],sol[1001],M,maxim;
int main()
{
    int i;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&x[i]);
        M+=x[i];
    }
    M/=n;
    sol[1]=0;
    sol[2]=M+sol[1]-x[1];
    for(i=3;i<n;i++)
    {
        sol[i]=M-sol[i-2]+2*sol[i-1]-x[i-1];
        if(sol[i]<0 && maxim<-sol[i])
            maxim=-sol[i];
    }
    sol[n]=x[n]+sol[n-1]-M;
    if(sol[n]<0 && maxim<-sol[n])
            maxim=-sol[n];
    if(maxim>0)
        for(i=1;i<=n;i++)
            sol[i]+=maxim;
    for(i=1;i<=n;i++)
        printf("%d\n",sol[i]);
    return 0;
}
