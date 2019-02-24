#include <cstdio>
using namespace std;
FILE *fin=freopen("fact.in","r",stdin);
FILE *fout=freopen("fact.out","w",stdout);
long long p;
int cinci(long long k)
{
    int x=0,c=5;
    while(k>=c)
    {
        x+=k/c;
        c*=5;
    }
    return x;
}
void cauta(long long a, long long b)
{
    long long sol=-1,m;
    while(b>a+1)
    {
        m=a+(b-a)/2;
        if(cinci(m)<p)
            a=m;
        else if(cinci(m)==p)
        {
            sol=m;
            b=m;
        }
        else
            b=m;
    }
    printf("%lld",sol);
}
int main()
{
    scanf("%lld",&p);
    if(p==0)
    {
        printf("1");
        return 0;
    }
    else
        cauta(-1,5*p+1);
    return 0;
}
