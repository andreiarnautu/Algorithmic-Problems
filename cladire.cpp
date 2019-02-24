#include <fstream>
using namespace std;
ifstream in("cladire.in");
ofstream out("cladire.out");
int x,y,mat[1001][1001],m,n,i,j,maxim=2;
long long k;
int minim(int a,int b,int c)
{
    if(a<=b && a<=c)
        return a;
    if(b<=a && b<=c)
        return b;
    return c;
}

int main()
{
    in>>m>>n>>k;
    for(i=0;i<k;i++)
    {
        in>>x>>y;
        mat[x][y]=1;
    }
    for(i=1;i<=n;i++)
        if(mat[1][i]!=1)
            mat[1][i]=2;
    for(i=1;i<=m;i++)
        if(mat[i][1]!=1)
            mat[i][1]=2;
    if(k!=m*n)
        maxim=2;
    else
        maxim=1;
    for(j=2;j<=n;j++)
    {
        for(i=2;i<=m;i++)
        {
            if(mat[i][j]!=1)
            {
                mat[i][j]=1+minim(mat[i-1][j-1],mat[i-1][j],mat[i][j-1]);
                if(mat[i][j]>maxim)
                    maxim=mat[i][j];
            }
        }
    }
    out<<maxim-1;
    return 0;
}
