#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("maraton1.in");
ofstream out("maraton1.out");
long long n,k,n2=1,i,t;
short x,v[5002],d;
int main()
{
    in>>n>>k;
    for(i=1;i<=n;i++)
    {
        in>>x;
        if(x==-2)
            v[i]=0;
        else if(x==-1)
            v[i]=5;
        else
            v[i]=8;
    }
    while(n2<=n)
    {
        t+=k;
        for(i=1;i<=n;i++)
            {v[i]=(v[i]+k+d)%10;}
        if(v[n2]!=8 && v[n2]!=9)
            d=8-v[n2];
        else
            d=0;
        t+=d;
      //  out<<endl;
        ++n2;
    }
    out<<t+k;
    return 0;
}
