#include <fstream>
using namespace std;
ifstream in("jump.in");
ofstream out("jump.out");

int main()
{
    long n,n1=1,n2=1,n3=2,aux,nr;
    in>>n;
    for(int i=3;i<=n;i++)
    {
        aux=n3%666013;
        n3+=(n1+n2)%666013;
        n1=n2%666013;
        n2=aux%666013;
    }
    out<<n3%666013;
    return 0;
}
