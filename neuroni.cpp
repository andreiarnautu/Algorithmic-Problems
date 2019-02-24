#include <cstdio>
using namespace std;
FILE *fin=freopen("neuroni.in","r",stdin);
FILE *fout=freopen("neuroni.out","w",stdout);
bool a[101][101];
int n,m,v[101],k;
int main()
{
    int i,j;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)
        if(i%2==1)
            for(j=1;j<=i;j++)
                a[i][j]=1;
    for(i=1;i<=m;i++)
    {
        k=1;
        for(j=1;j<n;j++)
        {
            if(a[j][k]==1)
            {
                a[j][k]=0;
                ++k;
            }
            else
                a[j][k]=1;
        }
        ++v[k];
       // printf("%d ",k);
    }
  //  printf("\n");
    for(i=1;i<=n;i++)
        printf("%d ",v[i]);
    return 0;
}
