#include <fstream>
using namespace std;
ifstream in("exp1.in");
ofstream out("exp1.out");
int m,n,f[30000],v[30000],maxim=0;
void ciur()
{
    int i,j;
    for(i=4;i<=30000;i+=4)
        v[i]=1;
    for(i=3;i<=30000;i++)
        if(v[i]==0)
            for(j=2*i;j<=30000;j+=i)
                v[j]=1;
}
void prim()
{
    int k=3,x;
    in>>x;
    while(x%2==0 && x)
    {
        ++f[2];
        x=x/2;
    }
    while(x>=2)
    {
        while(x%k==0 && x!=0)
        {
            ++f[k];
            x=x/k;
        }
        if(k>maxim)
            maxim=k;
        k+=2;
    }
}
int natural()
{
    if(f[2]%m!=0)
        return 0;
    f[2]/=m;
    for(int i=3;i<=maxim;i+=2)
    {
        if(f[i]%m!=0)
            return 0;
        f[i]/=m;
    }
    return 1;
}
void afisare()
{
    out<<1<<endl;
    if(f[2]!=0)
    {
        out<<"2 "<<f[2]<<endl;
    }
    for(int i=3;i<=maxim;i+=2)
        if(f[i]!=0)
            out<<i<<" "<<f[i]<<endl;
}
int main()
{
    in>>m>>n;
    for(int i=0;i<=n;i++)
        prim();
    if(natural()==0)
        out<<"0";
    else
        afisare();
    return 0;
}
