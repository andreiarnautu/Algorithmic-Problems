#include <fstream>
using namespace std;
ifstream in("alice.in");
ofstream out("alice.out");
long long n,k,x,parmaxim=0,a,b,numere;
int complementare(long long e)
{
    int cm=-1,nrc=0,nrm=0,i,f;
    f=e;
    while(e>0)
    {
        if(e%10>cm)
            cm=e%10;
        ++nrc;
        e/=10;
    }
    for(i=1;i<=nrc;i++)
        nrm=nrm*10+cm;
    return nrm-f;
}
int main()
{
    long long i;
    in>>n>>k;
    for(i=0;i<n;i++)
    {
        in>>x;
        if(x%2==0 && x>parmaxim)
            parmaxim=x;
        a=x;
        b=x;
        do
        {
            x=b;
            b=a;
            a=complementare(a);
          //  out<<a<<x<<b<<endl;
        }while(a>9 && a!=x && b!=a);
     //   out<<a<<endl;
        if(a==k)
            ++numere;
    }
    out<<parmaxim<<'\n'<<numere;
    return 0;
}
