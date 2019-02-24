#include <cstdio>
using namespace std;
FILE *fin=freopen("flip.in","r",stdin);
FILE *fout=freopen("flip.out","w",stdout);
long a[20][20],m,n,v[20];
long long maxim=-256000001;
long long verifica()
{
    long long s=0;
    for(int i=0;i<n;i++)
    {
        long long l=0;
        for(int j=0;j<m;j++)
            l+=v[j]*a[i][j];
        if(l>0)
            s+=l;
        else
            s-=l;
    }
    return s;
}
void gen(int k)
{
    long long s;
    if(k==m)
    {
        s=verifica();
        if(s>maxim)
            maxim=s;
    }
    else
    {
        v[k]=1;
        gen(k+1);
        v[k]=-1;
        gen(k+1);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&a[i][j]);
    for(int i=0;i<20;i++)
        v[i]=1;
    gen(0);
    printf("%lld",maxim);
    return 0;
}
