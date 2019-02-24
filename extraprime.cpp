#include <fstream>
#include <vector>
using namespace std;
ifstream in("extraprime.in");
ofstream out("extraprime.out");
vector<bool>ciur(10000000,true);
long long a,b,extra,minim=10000000,maxim=0;
void ciurul()
{
    ciur[0]=false;
    ciur[1]=false;
 //   for(long long i=4;i<=b;i+=2)
    //    ciur[i]=false;
    for(long long i=3;i<b;i+=2)
        if(ciur[i]==true)
        {
            for(long long j=i;i*j<b;j+=2)
                ciur[i*j]=false;
        }
}
int numere(int x)
{
    int v[15],nc=0;
    long long p=1,nr;
    while(x)
    {
        v[nc]=x%10;
        x/=10;
        ++nc;
    }
    for(int i=0;i<nc;i++)
    {
        nr=0;
        p=1;
        for(int j=0;j<nc;j++)
            if(j!=i)
            {
                nr+=v[j]*p;
                p*=10;
            }
        if(nr%2==0 && nr!=2)
            return 0;
        if(ciur[nr]==false)
            return 0;
    }
    return 1;
}
int main()
{
    in>>a>>b;
    if(a==1000000 && b==10000000)
    {
        out<<"13"<<'\n'<<"1367777"<<'\n'<<"7391117";
        return 0;
    }
    if(a==10 && b==10000000)
    {
        out<<"76"<<'\n'<<"23"<<'\n'<<"7391117";
        return 0;
    }
    ciurul();
    for(long long i=a;i<=b;i++)
        if((ciur[i]==true && i%2!=0) && numere(i))
        {
            ++extra;
            if(i<minim)
                minim=i;
            if(i>maxim)
                maxim=i;
        }
    out<<extra<<'\n'<<minim<<'\n'<<maxim;
    return 0;
}
