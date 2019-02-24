#include <fstream>
using namespace std;
ifstream in("betasah.in");
ofstream out("betasah.out");
int n,d,k,nr,maxim;
short m[1000][1000];
int main()
{
    int i,j,x,y;
    in>>n>>d>>k;
    /*for(i=1;i<=n;i++)
        for(j=i+1;j<=n;j++)
            m[i][j]=2;*/
    for(i=1;i<=d;i++)
    {
        in>>x>>y;
        m[x][y]=1;
    }
    for(i=1;i<=k;i++)
    {
        in>>x>>y;
        m[x][y]=-1;
    }
    for(i=1;i<=n;i++)
    {
        nr=0;
        for(j=1;j<=i;j++)
            if(m[i][j]!=-1)
                ++nr;
        if(nr>maxim)
            maxim=nr;
    }
    out<<maxim<<'\n';
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            if(m[i][j]==1)
            {

            }
    return 0;
}
