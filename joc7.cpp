#include <cstdio>
using namespace std;
FILE *fin=freopen("joc7.in","r",stdin);
FILE *fout=freopen("joc7.out","w",stdout);
int m,n;
int a[31][31],f[32],lmax=1,l=1;
void cauta(int x, int y)
{
    if(x>0 && !f[a[x-1][y]])
    {
        ++l;
        if(l>lmax)
            lmax=l;
        f[a[x-1][y]]=1;
        cauta(x-1,y);
        f[a[x-1][y]]=0;
        --l;
    }
    if(y>0 && !f[a[x][y-1]])
    {
        ++l;
        if(l>lmax)
            lmax=l;
        f[a[x][y-1]]=1;
        cauta(x,y-1);
        f[a[x][y-1]]=0;
        --l;
    }
    if(x<m-1 && !f[a[x+1][y]])
    {
        ++l;
        if(lmax<l)
            lmax=l;
        f[a[x+1][y]]=1;
        cauta(x+1,y);
        f[a[x+1][y]]=0;
        --l;
    }
    if(y<n-1 && !f[a[x][y+1]])
    {
        ++l;
        if(l>lmax)
            lmax=l;
        f[a[x][y+1]]=1;
        cauta(x,y+1);
        f[a[x][y+1]]=0;
        --l;
    }
}
int main()
{
    int i,j;
    char c;
    scanf("%d%d",&m,&n);
    getchar();
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            c=getchar();
            a[i][j]=c-65;
        }
        getchar();
    }
    f[a[0][0]]=1;
    cauta(0,0);
    printf("%d",lmax);
    return 0;
}
