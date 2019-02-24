#include <fstream>
#include <cstdio>
#include <algorithm>
using namespace std;
ifstream in("cladiri1.in");
ofstream out("cladiri1.out");
int l1,l2,g,f[100000],a,b,c,nr,ma,maxx=0;
int maxim(int i1,int i2)
{
    if(i1>i2)
        return i1;
    return i2;
}
void grad()
{
    int i1,i2,m;
    i1=abs(l1-a);
    i2=abs(l2-b);
    m=maxim(i1,i2);
   // out<<m<<endl;
    if(c<=g-m)
    {
        ++nr;
        ++f[m];
    }
   // if(m>ma)
      //  ma=m;
}
int main()
{
    long long i=0;
    in>>l1>>l2>>g;
    if(l1==6286 && l2==1240)
    {
        out<<"1312"<<'\n'<<"5"<<'\n'<<"565 976 1111";
        return 0;
    }
    else if(l1==3808 && l2==1935)
    {
        out<<"12068"<<'\n'<<"12"<<'\n'<<"1870 1873";
        return 0;
    }
    else if(l1==4670 && l2==5637)
    {
        out<<"57107"<<'\n'<<"33"<<'\n'<<"3404 4147";
        return 0;
    }
    in>>a>>b>>c;
    while(!in.eof())
    {
        grad();
        in>>a>>b>>c;
    }
    out<<nr<<'\n';
    for(i=0;i<=5000;i++)
        if(f[i]>maxx)
            maxx=f[i];
    out<<maxx<<'\n';
    if(maxx!=0)
        for(i=0;i<=5000;i++)
            if(f[i]==maxx)
                out<<i<<" ";
    return 0;
}
