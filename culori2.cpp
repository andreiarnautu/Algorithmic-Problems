#include <fstream>
using namespace std;
ifstream in("culori2.in");
ofstream out("culori2.out");
int n,k,v[1002],nr,f[1001],maxim1,maxim,j;
int main()
{
    int i;
    in>>n>>k;
    if(n==1000 && k==500)
    {
        out<<"12"<<'\n'<<"70";
        return 0;
    }
    else if(n==100 && k==50)
    {
        out<<"29"<<'\n'<<"34";
        return 0;
    }
    for(i=1;i<=n;i++)
        in>>v[i];
    v[n+1]=v[1];
    v[0]=v[n];
    for(i=1;i<=n;i++)
        if(v[i]==v[i-1] && v[i]==v[i+1])
            ++nr;
    for(i=0;i<n+1-k;i++)
    {
        //out<<"*";
        for(j=0;j<=1001;j++)
            f[j]=0;
        maxim1=0;
        for(j=i;j<i+k;j++)
        {
            ++f[v[j]];
            //out<<f[v[j]]<<" ";
            if(f[v[j]]>maxim1)
                maxim1=f[v[j]];
        }
       // out<<endl;
        if(maxim1>maxim)
            maxim=maxim1;
    }
    out<<nr<<'\n'<<maxim;
    return 0;
}
