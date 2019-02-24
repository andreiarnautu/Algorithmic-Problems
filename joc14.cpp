#include <cmath>
#include <cstdio>
using namespace std;
FILE *fin=freopen("joc14.in","r",stdin);
FILE *fout=freopen("joc14.out","w",stdout);
int n,ff[10],f[10],o[10],k,j,l,ok[10];
int main()
{
    int i,nr=0,x,maxim;
    scanf("%d", &n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&x);
        ++f[x];
    }
    for(i=1;i<=9;i++)
        if(f[i])
            ++nr;
    printf("%d\n",nr);
    printf("%.0f\n",trunc(sqrt(double(n))));
    l=trunc(sqrt(double(n)));
    for(i=1;i<=9;i++)
    {
        maxim=0;
        for(j=1;j<=9;j++)
            if(f[j]>maxim && ok[j]!=1)
            {
                maxim=f[j];
                k=j;
            }
        o[i]=k;
       // out<<o[i]<<endl;
        ok[k]=1;
    }
    nr=1;
    for(i=1;i<=l;i++)
    {
        for(j=1;j<=l;j++)
         {
            if(f[o[nr]]>0)
            {
                printf("%d",o[nr]);
                --f[o[nr]];
            }
            else
            {
                ++nr;
                printf("%d",o[nr]);
                --f[o[nr]];
            }
         }
        printf("\n");
    }
    return 0;
}
