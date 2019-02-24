#include <fstream>
using namespace std;
ifstream in("maroco.in");
ofstream out("maroco.out");
long long n,i,j,p[111],mat[111][111],nr,nr2,l,k,v[111];
long long n1,n2;
int main()
{
    in>>n;
    for(i=1;i<=n;i++)
    {
        in>>p[i];
        in>>v[i];
        for(j=1;j<=v[i];j++)
            in>>mat[i][j];
    }
    for(i=0;i<n;i++)
    {
        nr=0;
        for(j=1;j<=n;j++)
            if(v[j]==0 && p[j]>nr)
            {
                nr=p[j];
                nr2=j;
            }
        //out<<nr<<endl;
        if(i%2==0)
            n1+=nr;
        else
            n2+=nr;
        v[nr2]=-1;
        for(j=1;j<=n;j++)
        {
            for(l=1;l<=v[j];l++)
                if(mat[j][l]==nr2)
                {
                    for(k=l;k<v[j];k++)
                        mat[j][k]=mat[j][k+1];
                    --v[j];
                    break;
                }
        }
    }
    if(n1>n2)
        out<<"1 "<<n1;
    else if(n1==n2)
        out<<"0 "<<n1;
    else
        out<<"2 "<<n2;
    return 0;
}
