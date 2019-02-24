//Algoritm de tip Fill
#include <cstdio>
using namespace std;
FILE *fin=freopen("fill.in","r",stdin);
FILE *fout=freopen("fill.out","w",stdout);
int m,n,a[100][100],ob,d1[4]={-1,0,1,0},d2[4]={0,1,0,-1};
void umple(int x, int y)
{
    if(a[x][y])
    {
        a[x][y]=0;
        for(int i=0;i<4;i++)
            umple(x+d1[i],y+d2[i]);
    }
}
int main()
{
    int i,j;
    scanf("%d%d",&m,&n);
    for(i=1;i<=n;i++)
        for(j=1;j<m;j++)
            scanf("%d",&a[i][j]);
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            if(a[i][j])
            {
                ++ob;
                umple(i,j);
            }
    printf("%d",ob);
    return 0;
}
