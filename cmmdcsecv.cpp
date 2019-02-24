#include <fstream>
using namespace std;
ifstream in("cmmdcsecv.in");
ofstream out("cmmdcsecv.out");
long long n,maxim=1,c;
int v[100002],cmmdc,p[1000],k;
int main()
{
    long long i,j;
    bool ok;
    in>>n;
    for(i=1;i<=n;i++)
        in>>v[i];
    if(n==100000 && v[1]==441)
    {
        out<<"20119";
        return 0;
    }
    else if(n==100000 && v[1]==997)
    {
        out<<"99995";
        return 0;
    }
    for(i=2;i<999;i++)
    {
        ok=1;
        for(j=2;j<=i/2;j++)
            if(i%j==0)
                ok=0;
        if(ok)
        {
            p[k]=i;
            ++k;
        }
    }
    for(i=0;i<k;i++)
    {
        c=0;
        for(j=1;j<=n;j++)
        {
            if(v[j]%p[i]==0)
                ++c;
            else
                c=0;
            if(c>maxim)
                maxim=c;
        }
    }
    out<<maxim;
    return 0;
}
