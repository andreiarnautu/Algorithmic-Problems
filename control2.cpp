#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("control.in");
ofstream out("control.out");

int v[201],v2[201];

int main()
{
    int n,k=0,nr,i,ok;
    in>>n;
    for(i=0;i<n;i++)
        in>>v[i];
    sort(v,v+n);
    nr=0;
    while(n)
    {
       v2[k]=1;
       ok=0;
       while(v[nr]==v[nr+1])
       {
           v2[k]++;
           n--;
           nr++;
           ok=1;
       }
       if(ok==0)
            ++nr;
       ++k;
       n--;
    }
    for(i=0;i<k;i++)
        out<<v2[i]<<" ";
    return 0;
}
