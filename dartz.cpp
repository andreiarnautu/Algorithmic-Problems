#include <fstream>
using namespace std;
ifstream in("dartz.in");
ofstream out("dartz.out");
long pos[1000];

void umple(int &n)
{
    int k=2;
    while(k*k*k-k<=n)
    {
        pos[k]=k*k*k-k;
        ++k;
    }
    n=k-1;
}

int main()
{
    int n,n1=0,n2=0,ok,nn,j,i;
    in>>n;
    n=n/2;
    nn=n;
    umple(nn);
    for(i=0;i*i*i-i<n;i++)
    {
        n1=i*i*i-i;
        n2=n-n1;
        ok=0;
        for(j=nn;j>1;j--)
            if(j*j*j-j==n2)
                {ok=1;break;}
        if(ok==1)
            break;
    }
    out<<i-1<<" "<<j-1<<" "<<i-1<<" "<<j-1;
    return 0;
}
