#include <cstdio>
using namespace std;
FILE *fin=freopen("munte3.in","r",stdin);
FILE *fout=freopen("munte3.out","w",stdout);
long v[101],a[101],nr;
int n,m;
bool g;
int main()
{
    int i,ok=0;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
        scanf("%d",&v[i]);
    do
    {
        ++ok;
        m=0;
        g=0;
        for(i=1;i<=n;i++)
        {
            if((i>1 && i<n) && (v[i-1]<v[i] && v[i]>v[i+1]))
            {
                ++nr;
                g=1;
            }
            else
            {
                ++m;
                a[m]=v[i];
            }
        }
        for(i=1;i<=m;i++)
            v[i]=a[i];
        n=m;
      /*  for(i=1;i<=n;i++)
            printf("%d ",v[i]);
        printf("\n");*/
        if(ok==1)
            printf("%d\n",nr);
    }while(g);
    printf("%d\n",nr);
    printf("%d\n",n);
    return 0;
}
