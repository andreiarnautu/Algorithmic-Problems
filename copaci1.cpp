#include <fstream>
using namespace std;
ifstream in("copaci1.in");
ofstream out("copaci1.out");
long long mat[101][101],n,m,c1[10000],c2[10000];
void sursa()
{
    long long ok=1,i,j,nr,runde=0,w,intrari=0;
    long long t;
    while(ok)
    {
       // out<<"*";
        ok=0;
        t=0;
        w=0;
        ++runde;
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
            {
                if(mat[i][j]==0)
                {
                    nr=0;
                    w=1;
                    if(mat[i-1][j]==1)
                        ++nr;
                    if(mat[i][j+1]==1)
                        ++nr;
                    if(mat[i][j-1]==1)
                        ++nr;
                    if(mat[i+1][j]==1)
                       ++nr;
                    if(nr>1)
                    {
                        c1[t]=i;
                        c2[t]=j;
                        t=t+3;
                        ok=1;
                    }
                }
            }
        //out<<t<<endl;

        for(i=0;i<=t;i++)
            mat[c1[i]][c2[i]]=1;
       /*for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
               out<<mat[i][j]<<" ";
            out<<endl;
        }*/
    }
        if(w==0)
            out<<runde-1;
        else
            out<<runde-1<<endl<<"IMPOSIBIL";

}
int main()
{
    int i,j,nn;
    in>>n>>m;
    nn=n;
    for(i=0;i<=n+1;i++)
        for(j=0;j<=m+1;j++)
            mat[i][j]=2;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            in>>mat[i][j];
        sursa();
    return 0;
}
