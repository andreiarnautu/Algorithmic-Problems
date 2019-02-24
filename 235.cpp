#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("235.in");
ofstream out("235.out");
long long n,nr,numar,j,y=1,p=0,k,p35[50],w;
long v[40000],point;
int verifica(long long x)
{
    if(x%3==0)
    {
        while(x%3==0)
            x/=3;
        if(x==1)
            return -1;
        return 0;
    }
    else if(x%5==0)
    {
        while(x%5==0)
            x/=5;
        if(x==1)
            return 1;
        return 0;
    }
    return 0;
}
int main()
{
    long long i,x;
    in>>n;
    i=1;
    x=1;
    while(x<=2000000000)
    {
        x*=3;
        p35[i]=x;
        ++i;
    }
    x=1;
    while(x<=2000000000)
    {
        x*=5;
        p35[i]=x;
        ++i;
    }
    sort(p35,p35+i);
    w=i;
    for(i=0;i<n;i++)
    {
        in>>x;
        if(binary_search(p35,p35+w,x))
        {
            ++point;
            ++nr;
            if(x%3==0)
                v[point]=v[point-1]-1;
            else
                v[point]=v[point-1]+1;
        }
    }
    out<<nr<<'\n';
    while(y<nr)
    {
        y*=2;
        ++p;
    }
    k=1;
    for(i=0;i<nr;i++)
        for(j=i+1;j<=nr;j++)
            if(v[j]-v[i]==0 && (j-i & (j-i-1)) == 0)
                ++numar;
    out<<numar;
    return 0;
}
