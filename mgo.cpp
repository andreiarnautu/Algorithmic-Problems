#include <fstream>
using namespace std;
ifstream in("mgo.in");
ofstream out("mgo.out");
int n,p,v[101];
int main()
{
    int i,j,x,l,n1=0,n2=0;
    in>>p>>n;
    for(i=0;i<n;i++)
    {
        in>>x;
        if(i%2==0)
            v[x]=1;
        else
            v[x]=2;
        for(j=x-1;j>0;j--)
            if(v[j]==v[x])
                break;
        if(j!=0)
            for(l=j+1;l<x;l++)
                if(v[l]!=v[x])
                    v[l]=0;
        for(j=x+1;j<=n;j++)
            if(v[j]==v[x])
                break;
        if(j<=n)
            for(l=x+1;l<j;l++)
                if(v[l]!=v[x])
                    v[l]=0;
       /* for(l=1;l<=p;l++)
            out<<v[l]<<" ";
        out<<'\n';*/
    }
    for(i=1;i<=n;i++)
    {
        if(v[i]==1)
            ++n1;
        else if(v[i]==2)
            ++n2;
    }
    out<<n1<<" "<<n2;
    return 0;
}
