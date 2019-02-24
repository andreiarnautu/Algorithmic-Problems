#include <fstream>
using namespace std;
ifstream in("atelier.in");
ofstream out("atelier.out");
int n,sa[10000],sb[10000];

int main()
{
    int n,i,a,b,maxim,imax=1,elem=1,zilea,incepe=1;
    in>>n;
    for(i=1;i<=n;i++)
    {
        in>>a>>b;
        sa[i]=sa[i-1]+a;
        sb[i]=sb[i-1]+b;
    }
    maxim=sa[1]+sb[n]-sb[1];
    for(i=2;i<=n-1;i++)
        if(sa[i]+sb[n]-sb[i]>=maxim)
        {
            maxim=sa[i]+sb[n]-sb[i];
            elem=1;
            imax=i;
            zilea=i;
        }
    for(i=1;i<=n-1;i++)
    {
        if(sb[i]+sa[n]-sa[i]>maxim)
            {
                maxim=sb[i]+sa[n]-sa[i];
                elem=2;
                imax=i;
                incepe=2;
                zilea=(n-i-2)/2-1;
            }
        else if(sb[i]+sa[n]-sa[i]==maxim)
            if(incepe!=1 && zilea<(n-i-2)/2-1)
            {
                maxim=sb[i]+sa[n]-sa[i];
                elem=2;
                imax=i;
                incepe=2;
                zilea=(n-i-2)/2-1;
            }
    }
    out<<maxim<<endl;
    if(elem==1)
        out<<"A"<<endl;
    else
        out<<"B"<<endl;
    out<<imax;
    return 0;
}
