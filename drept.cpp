#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("drept.in");
ofstream out("drept.out");
long long n,f[1000000];
long long a,b,c,d,x,y;
int main()
{
    long long i,maxim=0;
    in>>n;
    for(i=1;i<=n;i++)
    {
        in>>a>>b>>c>>d;
        x=abs(c-a);
        y=abs(d-b);
        if(x>y)
            swap(x,y);
        ++f[x*1000+y];
        if(f[x*1000+y]>maxim)
            maxim=f[x*1000+y];
    }
    out<<maxim;
    return 0;
}
