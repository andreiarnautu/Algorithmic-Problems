#include <fstream>
using namespace std;
ifstream fin("cristal.in");
ofstream fout("cristal.out");
int n, m, a[55][55],v[55],vv[55],i;
void citire()
{
    int i,x,y;
    fin>>n>>m;
    for(i=1;i<=m;i++)
    {
        fin>>x>>y;
        a[x][y]=a[y][x]=1;
    }
}
void elimina(int i)
{
   int j;
   for(j=1;j<=n;j++)
        {
            v[j]=a[i][j];
            vv[j]=a[j][i];
            a[i][j]=0;
            a[j][i]=0;
        }
}
void restaureaza(int i)
{
   int j;
   for(j=1;j<=n;j++)
        {
            a[i][j]=v[j];
            a[j][i]=vv[j];
            v[j]=0;vv[j]=0;
        }
}
int conex(int i)
{
   int x0, viz[55], j, c[55], p, u,w;
   for(j=1;j<=n;j++)viz[j]=0;
   if(i==1)x0=2;
   else x0=1;
   p=u=1; c[p]=x0;viz[x0]=1;
   while(p<=u)
   {
       w=c[p];p++;
       for(j=1;j<=n;j++)
        if(a[w][j]==1&&viz[j]==0)
        {
            viz[j]=1;
            u++;
            c[u]=j;
        }
   }
   for(j=1;j<=n;j++)
    if(viz[j]==0&&j!=i)return 0;
   return 1;
 }
int main()
{
    citire();
    for(i=1;i<=n;i++)
    {
        elimina(i);
        if(conex(i))
            fout<<i<<' ';
        restaureaza(i);
    }
    return 0;
}
