#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("ozn1.in");
ofstream out("ozn1.out");
long long point,a,b,n,k,c,d,p[20000],maxim;
int v[2000000];
unsigned long s;
short nr;
int main()
{
    long long i,j;
    in>>n>>k;
    for(i=0;i<n;i++)
    {
            in>>a>>b>>c>>d>>nr;
            v[a]+=nr;
            v[c+1]-=nr;
    }
    for(i=0;i<k;i++)
    {
        in>>p[i];
        if(p[i]>maxim)
            maxim=p[i];
    }
    sort(p,p+k);
    for(i=0;i<=p[0];i++)
        s+=v[i];
    j=1;
    out<<s<<'\n';
    for(i=p[0]+1;i<=maxim;i++)
    {
        s+=v[i];
        if(i==p[j])
        {
            out<<s<<'\n';
            ++j;
        }
    }
    return 0;
}
