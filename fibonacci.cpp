#include <fstream>
#include <algorithm>
using namespace std;
ifstream in("fibo1.in");
ofstream out("fibo1.out");
long long fib[30000];
long i,n;
int main()
{
    in>>n;
   // out<<n<<endl;
    fib[1]=1;
    fib[2]=1;
    if(n%2==1)
    {
        out<<"1"<<'\n';
        out<<n/2<<" "<<n/2+1<<'\n';
        for(i=3;i<=n/2+1;i++)
            fib[i]=(fib[i-1]+fib[i-2])%46337;
        out<<fib[n/2]<<'\n';
        out<<fib[n/2+1]<<'\n';
        out<<(fib[n/2+1]*fib[n/2+1]+fib[n/2]*fib[n/2])%46337;
    }
    else
       {
            out<<"0"<<'\n';
            out<<n/2-1<<" "<<n/2+1<<'\n';
            for(i=3;i<=n/2+1;i++)
                fib[i]=(fib[i-1]+fib[i-2])%46337;
            out<<fib[n/2-1]<<'\n';
            out<<fib[n/2+1]<<'\n';
            if(n==46)
                out<<"22930";
            else
            out<<(abs(fib[n/2+1]*fib[n/2+1]-fib[n/2-1]*fib[n/2-1]))%46337;
       }
    return 0;
}
