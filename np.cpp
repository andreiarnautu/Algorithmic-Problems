#include <fstream>
using namespace std;
ifstream in("np.in");
ofstream out("np.out");
long long n,i,s,p=1,x;
int main()
{
    in>>n;
    while(n)
    {
        x=n%2;
        n=n/2;
        s+=p*x;
        p*=3;
    }
    out<<s;
    return 0;
}
