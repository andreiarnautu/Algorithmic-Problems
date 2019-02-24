#include <cstdio>
using namespace std;
FILE *fin=freopen("bila.in","r",stdin);
FILE *fout=freopen("bila.out","w",stdout);
int n,m;
long a[125][125],b[125][125],nr;
bool viz[125][125];
void Read()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&a[i][j]);
}
void Find(int x, int y)
{
    long x1,y1;
    long mi;
    mi=a[x][y];
    viz[x][y]=1;
    if(x>0 && a[x-1][y]<mi)
    {
        mi=a[x-1][y];
        x1=x-1;
        y1=y;
    }
    if(y>0 && a[x][y-1]<mi)
    {
        mi=a[x][y-1];
        x1=x;
        y1=y-1;
    }
    if(x<n-1 && a[x+1][y]<mi)
    {
        mi=a[x+1][y];
        x1=x+1;
        y1=y;
    }
    if(y<m-1 && a[x][y+1]<mi)
    {
        x1=x;
        y1=y+1;
    }
    if(mi==a[x][y])
        return;
    if(!viz[x1][y1])
        Find(x1,y1);
    b[x][y]+=b[x1][y1];
    if(b[x][y]>nr)
        nr=b[x][y];
}
void Solve()
{
    long minim=100000;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            b[i][j]=1;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(!viz[i][j])
                Find(i,j);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(a[i][j]<minim && b[i][j]==nr)
                minim=a[i][j];
    printf("%d %d",nr,minim);
}
int main()
{
    Read();
    Solve();
    return 0;
}
