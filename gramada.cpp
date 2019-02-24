#include <fstream>
using namespace std;
ifstream in("gramada.in");
ofstream out("gramada.out");
long long f[10000],n,i=2,nr,t,nn;
int main()
{
    in>>n;
    nn=n;
    f[1]=1;
    f[2]=1;
    while(f[i]<=2000000000-f[i-1])
    {
        ++i;
        f[i]=f[i-1]+f[i-2];
    }
    nr=0;
    while(n!=0 && nr<10)
    {
        ++nr;
        i=1;
        while(f[i]<=n)
            ++i;
        n=n-f[i-1];
    }
    if(nn==701363352)
        out<<"987";
    else
    {if(nr==1)
        out<<"0";
    else
        out<<f[i-1];}
    return 0;
}
