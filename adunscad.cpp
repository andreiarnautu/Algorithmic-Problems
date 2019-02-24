#include <fstream>
using namespace std;
ifstream in("adunscad.in");
ofstream out("adunscad.out");
int n,m,v[20],x[20];
void rezolvare()
{
    int g=1,i,j,s,ok=1;
    while(g)
    {
        g=0;
        s=0;
        for(i=m-1;i>=0;i--)
            if(x[i]==0)
            {
                g=1;
                break;
            }
        if(g==1)
        {
            x[i]=1;
            for(j=i+1;j<m;j++)
                x[j]=0;
        }
        for(i=0;i<m;i++)
        {
            if(x[i]==0)
                s-=v[i];
            else
                s+=v[i];
        }
        if(s==n)
        {
            break;
            ok=0;
        }
    }
    if(g==0 && ok==1)
        out<<"0"<<endl;
    else
    {
        if(x[0]==0)
            out<<"-"<<v[0];
        else
            out<<v[0];
        for(i=1;i<m;i++)
        {
            if(x[i]==0)
                out<<"-";
            else
                out<<"+";
            out<<v[i];
        }
    }
}
int main()
{
    int i,s1=0,s2=0;
    in>>n>>m;
    for(i=0;i<m;i++)
    {
        in>>v[i];
        s1+=v[i];
        s2-=v[i];
    }
    if(s1<n && s2>n)
        out<<"0"<<endl;
    else if(s2==n)
        for(i=0;i<m;i++)
            out<<"-"<<v[i];
    else
        rezolvare();
    return 0;
}
