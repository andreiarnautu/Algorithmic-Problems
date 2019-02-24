#include <fstream>
#include <bitset>
using namespace std;
ifstream in("control.in");
ofstream out("control.out");
bitset <10001> viz;
int frecv[200],v[200];

void ciur(int n)
{
    int i,j;
    for(j=4;j<=n;j+=2)
        viz[j]=1;
    for(i=3;i<=n;i+=2)
        if(viz[i]==0)
            for(j=3*i;j<=n;j+=2*i)
                viz[j]=1;
}

void citire(int n)
{
    int x;
    for(int i=0;i<n;i++)
    {
        in>>x;
        ++frecv[x];
    }
}

void pasul2()
{
    int i,k=0,u=0,z=0,p;
    for(i=0;i<=200;i++)
    {
        if(frecv[i]!=0)
        {
            p=frecv[i];
            v[k]=p;
            ++k;
        }
    }
    k=(k-1)/3;
    k=k*3;
    for(i=0;i<k;i+=3)
    {
        if(v[i]%2==0 && v[i+1]%2==0 && v[i+2]%2==0)
            ++u;
        else
            {
                ++z;
            }
    }
    out<<z*10+u<<endl;
    ciur(z*10+u);
    if(viz[z*10+u]==1)
        out<<"0";
    else
        out<<"1";
}

int main()
{
    int n;
    in>>n;
    citire(n);
    pasul2();
    return 0;
}
