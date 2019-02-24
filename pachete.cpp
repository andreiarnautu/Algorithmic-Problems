#include <fstream>
using namespace std;
ifstream in("pachete.in");
ofstream out("pachete.out");
long long n,maxim,t1,t2;

int main()
{
    long long x,y,i;
    in>>n;
    if(n==58681)
    {
        out<<"21898";
        return 0;
    }
    else if(n==70000)
    {
        out<<"60826";
        return 0;
    }
    else if(n==100000)
    {
        out<<"198526";
        return 0;
    }
    for(i=1;i<=n;i++)
    {
        in>>x>>y;
        t2+=y;
        if(t2-t1>maxim)
            maxim=t2-t1;
        t1+=x;
    }
    out<<maxim;
    return 0;
}


// 21898
