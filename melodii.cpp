#include <fstream>
using namespace std;
ifstream in("melodii.in");
ofstream out("melodii.out");
long long a,b,c,n,i,j,nr,r;
int main()
{
    in>>n>>r;
    for(i=1;i<=n;i++)
    {
        in>>nr;
        b=1;
        a=2;
        for(j=3;j<=nr;j++)
        {
            c=a+b;
            c%=r;
            b=a;
            a=c;
        }
        if(nr==1)
            c=1;
        if(nr==2) c=2; out<<c<<'\n';
    }
    return 0;
}
