#include <cstdio>
using namespace std;
FILE *f=freopen("doitrei.in","r",stdin);
FILE *g=freopen("doitrei.out","w",stdout);

int n,v1[101],v2[101],w[202];
void inmulteste()
{
    int i,j,t=0;
    w[0]=v1[0]+v2[0]-1;
    for(i=1;i<=v1[0];i++)
        for(j=1;j<=v2[0];j++)
            w[i+j-1]+=v1[i]*v2[j];
    for(i=1;i<=w[0];i++)
    {
        w[i]+=t;
        t=w[i]/10;
        w[i]%=10;
    }
    if(t)
    {
        ++w[0];
        w[w[0]]=t;
    }
    //scanf("2");
    for(i=w[0];i>0;i--)
        printf("%d",w[i]);
}
int main()
{
    int i;
    scanf("%d",&n);
    v1[0]=n; v1[n]=2;
    v2[0]=n; v2[n]=2;
    for(i=1;i<n;i++)
    {
        v1[i]=3;
        v2[i]=3;
    }
    inmulteste();
    return 0;
}
