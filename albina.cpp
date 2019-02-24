#include <cstdio>
using namespace std;
FILE *fin=freopen("albina.in","r",stdin);
FILE *fout=freopen("albina.out","w",stdout);
int d1[4]={-1,0,1,0};
int d2[4]={0,1,0,-1};
int a[32][32],b[32][32],n,m,i1,j1,h1,h2;
void umple(int x, int y)
{
    int i2,j2;
    b[x][y]=1;
    for(int i=0;i<4;i++)
    {
        i2=x+d1[i];
        j2=y+d2[i];
        if(!b[i2][j2])
        {
            if((a[x][y]>=a[i2][j2]) && (a[x][y]-a[i2][j2]<=h2))
                umple(i2,j2);
            if((a[x][y]<a[i2][j2]) && (a[i2][j2]-a[x][y]<=h1))
                umple(i2,j2);
        }
    }
}
int aria()
{
    int i,j,k,l,i2,j2,maxim=0,p;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            if(b[i][j])
                for(k=i;k<=n;k++)
                    for(l=j;l<=m;l++)
                        if(b[k][l])
                        {
                            p=1;
                            for(i2=i;i2<=k;i2++)
                            {
                                for(j2=j;j2<=l;j2++)
                                    if(b[i2][j2]==0)
                                    {
                                        p=0;
                                        break;
                                    }
                                if(!p)
                                    break;
                            }
                            if(p)
                                if((k-i+1)*(l-j+1)>maxim)
                                    maxim=(k-i+1)*(l-j+1);
                        }
    return maxim;
}
int main()
{
    int i,j;
    scanf("%d%d",&n,&m);
    scanf("%d%d",&i1,&j1);
    scanf("%d%d",&h1,&h2);
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    umple(i1,j1);
    printf("%d",aria());
    return 0;
}
