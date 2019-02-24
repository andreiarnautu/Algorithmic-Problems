#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("onigim.in");
ofstream out("onigim.out");
int n,k,p[1002],a[1002],a2[1002],x,f[1002];
void cerinta1()
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<x;j++)
            if(a[i]==a2[j])
                break;
        out<<p[j]<<" ";
    }
    out<<endl;
}
void cerinta2()
{
    int nr=0,i;
    for(i=0;i<n;i++)
        if(a[i]==a2[x-1] || a[i]==a2[x-2] || a[i]==a2[x-3])
            ++nr;
    out<<nr<<endl;
}
void cerinta3()
{
    int maxim=0,i;
    for(i=0;i<n;i++)
        ++f[a[i]];
    for(i=0;i<1001;i++)
        if(f[i]>maxim)
            maxim=f[i];
    out<<maxim;
}
int main()
{
    int i,ok,j;
    for(i=0;i<1001;i++)
        a2[i]=1002;
    in>>n>>k;
    for(i=0;i<k;i++)
        in>>p[i];
    for(i=0;i<n;i++)
    {
        in>>a[i];
        ok=0;
        for(j=0;j<=x;j++)
            if(a2[j]==a[i])
                {ok=1;break;}
        if(ok==0)
        {
            a2[x]=a[i];
            ++x;
        }
    }
    sort(a2,a2+x);
    //for(i=0;i<x;i++)
      //  out<<a2[i]<<" ";
    cerinta1();
    cerinta2();
    cerinta3();
    return 0;
}
