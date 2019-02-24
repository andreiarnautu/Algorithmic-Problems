#include <cstdio>
#include <vector>
using namespace std;
FILE *fin=freopen("ciur.in","r",stdin);
FILE *fout=freopen("ciur.out","w",stdout);
char p[100000];
long long n;
void ciur()
{
    long long i, j, nr = 1;
    for (i=1;((i*i)<<1)+(i<<1)<=n;i+=1)
        if ((p[i>>3]&(1<<(i&7)))==0)
            for (j=((i*i)<<1)+(i<<1);(j<<1)+1<=n;j+=(i<<1)+1)
                p[j>>3]|=(1<<(j&7));
    for(i=1;2*i+1<=n;++i)
       if((p[i>>3]&(1<<(i&7)))==0)
           nr++;
    printf("%lld",nr);
}
int main()
{
    scanf("%lld",&n);
    ciur();
    return 0;
}
