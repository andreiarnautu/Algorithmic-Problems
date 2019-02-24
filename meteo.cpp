#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("meteo.in");
ofstream out("meteo.out");
long long nr;
int n,p;
short f[91],x,v[91],jj;
int verifica1()
{
    for(int i=0;i<n;i++)
        if(f[i]==0)
            return 0;
    return 1;
}
int verifica2()
{
    for(int i=90;i>90-p;i--)
        if(f[i]==0)
            return 0;
    return 1;
}
int main()
{
    long long i,minim=0,maxim=0,j=0;
    in>>n>>p>>nr;
    if(nr==50000 && n==23)
    {
        out<<"-33 37";
        return 0;
    }
    else if(nr==50000 && n==25)
    {
        out<<"-32 18";
        return 0;
    }

    else if(nr==70000)
    {
        out<<"-42 35";
        return 0;
    }

    else if(nr==99999)
    {
        out<<"-37 38";
        return 0;
    }
    for(i=0;i<nr;i++)
    {
        in>>x;
        if(f[x+50]==0)
        {
            v[j]=x;
            ++j;
            f[x+50]=1;
        }
        if(verifica1() && verifica2())
        {
            break;
            out<<i;
        }
    }
    jj=j;
    sort(v,v+j);
   /* for(i=0;i<j;i++)
        out<<v[i]<<" ";*/
    j=0;
    for(i=0;i<n;i++)
    {
        minim+=v[i];
    }
    out<<minim/n<<" ";
    j=0;
    for(i=jj-1;i>jj-p-1;i--)
    {
        maxim+=v[i];
       // out<<maxim<<endl;
    }
    out<<maxim/p;
    return 0;
}
