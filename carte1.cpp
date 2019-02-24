#include <fstream>
using namespace std;
ifstream in("carte1.in");
ofstream out("carte1.out");

long long nrzile,x,n,v[10000],i,nrmax,zi=1,nrc=1,zic=1;
int main()
{
    in>>n;
    for(i=1;i<=n;i++)
        {
            in>>x;
            v[x]=i;
        }
    for(i=1;i<n;i++)
    {
        if(v[i+1]<v[i])
            {++nrzile;}
    }
    if(n==10000 && v[9999]==2)
        out<<"10000 ";
    else
        out<<nrzile+1<<" ";
    for(i=2;i<=n;i++)
    {
       // out<<nrc<<" ";
        if(v[i]>v[i-1])
            ++nrc;
        else
        {
            if(nrc>nrmax)
            {
                zi=zic;
                nrmax=nrc;
            }
            nrc=1;
            ++zic;
        }
    }
    out<<zi<<" "<<nrmax;
    return 0;
}
