#include <fstream>
using namespace std;
ifstream in("greieri.in");
ofstream out("greieri.out");
long long ok,aux,n,m,p,v[100000],k,s=1,i;
int main()
{
    in>>n>>m;
    out<<n*(n-1)<<'\n';
    m=m%(n*(n-1));
    for(i=1;i<=n;i++)
        v[i]=i;
    k=n;
   // out<<m<<'\n';
    while(s<=m)
    {
        ok=0;
        while(s<=m && k>=2)
        {
            ok=1;
            aux=v[k];
            v[k]=v[k-1];
            v[k-1]=aux;
            --k;
            ++s;
        }
        if(ok==0)
            ++s;
        k=n;
    }
    for(i=1;i<=n;i++)
        out<<v[i]<<" ";
    return 0;
}
