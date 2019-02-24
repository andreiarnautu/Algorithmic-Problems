#include <fstream>
using namespace std;
ifstream in("moretime.in");
ofstream out("moretime.out");
long long nr,n,i,v[10000],v2[10000],j=1,x1,x2,s[10000],ok;
int verifica(int k)
{
    int u,u2;
    u=k%10;
    while(k)
    {
        u2=k%10;
        k=k/10;
    }
    if(u2==u)
        return 1;
    return 0;
}
int main()
{
    in>>n;
    for(i=1;i<=n;i++)
    {
        in>>x1>>x2;
        if(verifica(x1))
        {
            ++nr;
            v[j]=x1;
            v2[j]=x2;
            ++j;
        }
    }
    out<<nr<<'\n';
    s[0]=0;
    for(i=1;i<j;i++)
    {
        s[i]=(s[i-1]+v2[i])%nr;
        if(s[i]==0)
        {
            out<<i<<'\n';
            for(x1=1;x1<=i;x1++)
                out<<v[x1]<<" ";
            ok=1;
        }
    }
    if(!ok)
    {for(x1=1;x1<j-1;x1++)
        for(x2=x1+1;x2<j;x2++)
            if(s[x1]==s[x2])
            {
                out<<x2-x1<<'\n';
                for(i=x1+1;i<=x2;i++)
                    out<<v[i]<<" ";
            }}
    return 0;
}
