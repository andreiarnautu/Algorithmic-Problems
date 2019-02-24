#include <cstdio>
#include <vector>
using namespace std;
FILE *fin=freopen("ciur.in","r",stdin);
FILE *fout=freopen("ciur.out","w",stdout);
vector<bool>v(2000010,false);
long long n;
void ciur()
{
    long long i,j,nr=1;
    printf("2 ");
    for(i=1;<=n;++i) // Ei faceau for (i = 1; ((i * i) << 1) + (i << 1) <= n; i += 1) Ceea ce e gresit, noua ne tb 2*i +1, nu 2*i^2+i. Si nu facea toate numerele prime.
        if(v[i]==false)
        {
            for(j=((i * i)<<1)+(i<<1);(j<<1)+ 1<=n; j+=(i<<1)+1)
                v[j]=true;
            printf("%lld ",i*2+1);
            ++nr;
        }
    printf("\n%lld",nr);
}
int main()
{
    scanf("%lld",&n);
    ciur();
    return 0;
}
