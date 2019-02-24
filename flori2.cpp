#include <fstream>
using namespace std;
ifstream in("flori2.in");
ofstream out("flori2.out");
int a[10000];

int main()
{
    int n,i,j;
    long s=0;
    in>>n;
    a[1]=1;
    a[2]=1;
    for(i=3;i<=2+n;i++)
    {
        a[i]=(a[i-2]%9001 + a[i-1]%9001)%9001;
    }
    out<<a[n+2]-1;
    return 0;
}
