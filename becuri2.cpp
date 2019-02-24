#include <fstream>
using namespace std;
ifstream in("becuri2.in");
ofstream out("becuri2.out");

int n,a,b,v[40]={2},s[30],k1,v2[40];
void transformarea()
{
    int k=0;
    while(a)
    {
        v[k]=a%2;
        a=a/2;
        ++k;
    }
    k1=k;

    for(int i=0;i<k;i++)
        if(v[i]==1)
            ++s[i];
}
void transformareb()
{
    int k=0,x,a1=0,a2=0;
    while(b)
    {
        v2[k]=b%2;
        b=b/2;
        ++k;
    }
    for(int i=0;i<31;i++)
    {
        if(v[i]==0 && v2[i]==1)
            ++a2;
        else if(v[i]==1 && v2[i]==0)
            ++a1;
    }
    out<<a1<<" "<<a2<<" ";
    for(int i=0;i<k;i++)
        if(v2[i]==1)
            ++s[i];
}
void finalizare()
{
    int k=0,nrc,lmax=0,ok;
    while(k<31)
    {
        nrc=0;
        ok=0;
        while(s[k]==2)
        {
            ++nrc;
            ++k;
            ok=1;
        }
        if(nrc>lmax)
            lmax=nrc;
        if(ok==0)
            ++k;
    }
    out<<lmax;
}

int main()
{
    in>>n>>a>>b;
    transformarea();
    transformareb();
    finalizare();
    return 0;
}
