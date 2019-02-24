#include <cstdio>
using namespace std;
FILE *fin=freopen("patrate.in","r",stdin);
FILE *fout=freopen("patrate.out","w",stdout);
int n,dx,dy;
long nr=0;
short a[51][51];
int verifica(int x, int y)
{
    if(x<dy+dx)
        return 0;
    if(y<dx)
        return 0;
    if(a[x][y]!=a[x-dx][y+dy])
        return 0;
    if(a[x-dy][y-dx]!=a[x][y])
        return 0;
    if(a[x][y]!=a[x-dy-dx][y+dy-dx])
        return 0;
    return 1;
}
void solve(int x, int y)
{
    for(dx=1;dx<=x;++dx)
        for(dy=0;dy<n-y;++dy)
        {
            if(verifica(x,y)==1)
                ++nr;
        }
}
int main()
{
    int i,j;
    scanf("%d",&n);
    for(i=0;i<50;i++)
        for(j=0;j<50;j++)
            a[i][j]=2;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&a[i][j]);
   /* for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }*/
    for(i=1;i<n;i++)
        for(j=0;j<n;j++)
            solve(i,j);
    printf("%d",nr);
    return 0;
}
