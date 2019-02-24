#include <fstream>
using namespace std;
ifstream in("cifre2.in");
ofstream out("cifre2.out");
long long n,aux,u,p=1,nr,c;
int main()
{
    in>>n>>c;
    while(n>=c)
    {
        u=n%10;
        if(u>c)
            nr+=(n/10 + 1)*p;
        else if(u==c)
            nr+=(n/10)*p+aux+1;
        else
            nr+=(n/10)*p;
        n/=10;
        aux+=p*u;
        p*=10;
    }
    out<<nr;
    return 0;
}
