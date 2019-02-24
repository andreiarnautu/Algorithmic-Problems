#include <fstream>
#include <bitset>
#include <algorithm>
using namespace std;
ifstream in("matrice4.in");
ofstream out("matrice4.out");
int v[2500],v2[2500],m,n;
int e[32771];
void ciur()
{
    int i,j;
    e[-1]=-1;
    for(i=4;i<=32771;i+=2)
        e[i]=1;
    for(i=3;i<=32771;i+=2)
        if(e[i]==0)
            for(j=2*i;j<=32771;j+=i)
                e[j]=1;
}
void sursa()
{
    int i,x,nr,t,ok=1,r=0;
    x=m*n;
    while(ok)
    {
        t=0;
        ++r;
        ok=0;
        for(i=0;i<x;i++)
        {
            if(e[v[i]]==0)
            {
                ++nr;
                v2[t]=v[i];
                v[i]=-1;
                ++t;
            }
            else if(e[v[i]]==1)
                ++v[i];
        }
        for(i=0;i<x;i++)
            if(v[i]!=-1)
            {
                ok=1;
                break;
            }
    }
    out<<r<<" "<<t<<endl;
    sort(v2,v2+t);
    for(i=0;i<t;i++)
        out<<v2[i]<<" ";
}
int main()
{
    int i;
    in>>n>>m;
    for(i=0;i<n*m;i++)
        in>>v[i];
    ciur();
    sursa();
    return 0;
}
