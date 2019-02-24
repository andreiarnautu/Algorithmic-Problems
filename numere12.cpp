#include<cstdio>
#include <fstream>
using namespace std;
ifstream in("numere12.in");
ofstream out("numere12.out");
FILE *f=freopen("numere12.in","r",stdin);
FILE *g=freopen("numere12.out","w",stdout);
long a=0,b=0,nr=0;
int verifica(long x)
{
    long xx;
    int u;
    xx=x;
    while(xx)
    {
        u=xx%10;
        if(u!=0)
            if(x%u!=0)
                return 0;
        xx/=10;
    }
    return 1;
}
int main()
{
    scanf("%d%d",&a,&b);
    for(long i=a;i<=b;i++)
        if(verifica(i))
            ++nr;
    printf("%d",nr);
    return 0;
}
