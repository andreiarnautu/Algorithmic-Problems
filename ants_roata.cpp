#include <fstream>

using namespace std;

ifstream f("ants.in");
ofstream g("ants.out");

int d[100001],v[100001];

int main()
{
    int s=0,li,ls,mij,i,n,dif,minim=1000000001,ok,det,nr;
    f>>n;
    for(i=1;i<=n;i++)
        {
            f>>d[i]>>v[i];
            s+=v[i];
            if(v[i]<minim)
                minim=v[i];
        }
    li=minim;
    ls=s/n;
    mij=(li+ls)/2;
    ok=0;
    while(ok==0)
    {
        nr=s-n*mij+d[1]-d[n];
        if(nr>0)
        {
            li=mij+1;
            mij=(li+ls)/2;
        }
        if(nr<0)
        {
            ls=mij-1;
            mij=(li+ls)/2;
        }
        if(nr==0)
        {
            ok=1;
            g<<mij;
        }
    }
    return 0;
}
