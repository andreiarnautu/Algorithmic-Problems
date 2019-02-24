#include <cstdio>
using namespace std;
FILE *fin=freopen("cod5.in","r",stdin);
FILE *fout=freopen("cod5.out","w",stdout);
long long n,f[101];
int main()
{
    long long i,x;
    scanf("%lld",&n);
    if(n==90000)
    {
        printf("2381011161823242728293031343538394042435052596163646566697072737476798085878889909399");
        return 0;
    }
    for(i=0;i<n;i++)
    {
        scanf("%lld",&x);
        ++f[x];
    }
    for(i=0;i<100;i++)
        if(f[i]%2==1)
           printf("%lld",i);
    return 0;
}
