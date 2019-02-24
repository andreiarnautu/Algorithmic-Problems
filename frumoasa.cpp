#include <fstream>
using namespace std;
ifstream in("frumoasa.in");
ofstream out("frumoasa.out");
long long i,n,p,s=1;
int minim(long long k)
{
    if(i>p)
        return 26-p;
    else
        return 26-i;
}
int main()
{
    in>>n>>p;
    for(i=0;i<n;i++)
        s=(s*minim(i))%1000000007;
    out<<s;
}
