#include <fstream>
using namespace std;
ifstream in("grupe.in");
ofstream out("grupe.out");
void fib(long n)
{
    int i;
    long long fib[95];
    fib[1]=1;
    fib[2]=1;
    for(i=3;i<=n+2;i++)
        fib[i]=fib[i-1]+fib[i-2];
    out<<fib[n+2]-1;
}
int main()
{
    long n;
    in>>n;
    fib(n);
    return 0;
}
