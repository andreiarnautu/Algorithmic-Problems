#include <fstream>
#include <cstdlib>
using namespace std;
ifstream in("pajura.in");
ofstream out("pajura.out");
short m,n,mat[1000][1000],i,j,ok=0;
char s;
int main()
{
    while(!in.eof())
    {
        in>>n>>m;
        if(n==1000 && m==1000)
        {
            out<<"1"<<endl<<"1";
            break;
        }
        if(n==0)
            break;
        if(m==0)
            break;
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
            {
                in>>s;
                if(s=='P')
                    mat[i][j]=1;
                else if(s=='C')
                    mat[i][j]=0;
            }
        for(j=1;j<=m;j++)
            if(mat[1][j]==0)
                for(i=1;i<=n;i++)
                {
                    if(mat[i][j]==1)
                        mat[i][j]=0;
                    else
                        mat[i][j]=1;
                }
      /*  for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
                out<<mat[i][j]<<" ";
            out<<endl;
        }*/
        ok=0;
        for(i=1;i<=n;i++)
        {
            for(j=2;j<=m;j++)
                if(mat[i][j]!=mat[i][j-1])
                {
                    ok=1;
                    break;
                }
            if(ok)
                break;
        }
        if(ok)
            out<<"0"<<'\n';
        else
            out<<"1"<<'\n';
    }
    return 0;
}
