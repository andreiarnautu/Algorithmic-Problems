#include <cstdio>
#include <vector>
using namespace std;
FILE *fin=freopen("prim.in","r",stdin);
FILE *fout=freopen("prim.out","w",stdout);
vector<bool>v(2147000,false);
long long n;
void ciur()
{
    long long i,j,nr=1,k=0;
    for (i=1;;i+=1)
        if(v[i]==false)
        {
            for(j=((i * i)<<1)+(i<<1);(j<<1)+ 1<=2000000; j+=(i<<1)+1)
                v[j]=true;
           // printf("%lld ",i*2+1);
            ++nr;
            if(nr==n+1)
            {
                k=(i<<1)+1;
                break;
            }
        }
    printf("%lld",k*k);
}
int main()
{
    scanf("%lld",&n);
    printf("%.3f",(float)sizeof(v)/(1024*1024));
    ciur();
    return 0;
}
