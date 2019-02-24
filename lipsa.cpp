#include <cstdio>
using namespace std;
FILE *fin=freopen("lipsa.in","r",stdin);
FILE *fout=freopen("lipsa.out","w",stdout);
long long n;
unsigned long long s,s2;
int main()
{
    long long x;
    scanf("%d",&n);
    s=n*(n+1)/2;
    for(long long i=1;i<n;i++)
    {
        scanf("%d",&x);
        s-=x;
    }
    printf("%d",s);
    return 0;
}
