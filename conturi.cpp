#include <fstream>
using namespace std;
ifstream in("conturi.in");
ofstream out("conturi.out");
int n,x;
long long a,maxim;
int main()
{
    int i;
    in>>n>>x;
    for(i=1;i<=n;i++)
    {
        in>>a;
        if(a/100000==x)
            if ((a/10000)%10==1)
                if(a%10000>maxim)
                    maxim=a%10000;
    }
    out<<maxim;
    return 0;
}
