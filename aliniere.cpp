#include <fstream>
using namespace std;
ifstream in("aliniere.in");
ofstream out("aliniere.out");
long long fib[300000],n,i;
int main()
{
    in>>n;
    fib[1]=1;
    fib[2]=2;
    for(i=3;i<=n;i++)
        fib[i]=(fib[i-1]+fib[i-2])%9973;
   // out<<i;
    out<<fib[i-1];
    return 0;
}
