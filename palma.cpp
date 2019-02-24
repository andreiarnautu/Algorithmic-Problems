#include <cstdio>
using namespace std;
FILE *fin=freopen("palma.in","r",stdin);
FILE *fout=freopen("palma.out","w",stdout);
int n,h;
long k[500],v[64001];
long long s,maxim;
void Read()
{
    int x;
    scanf("%d%d%I64d",&n,&h,&s);
    for(int i=0;i<n;i++)
        scanf("%d",&k[i]);
    for(int i=0;i<n;i++)
        for(int j=0;j<h;j++)
        {
            scanf("%d",&x);
            if(x<k[i])
            {
                ++v[x];
                if(x>maxim)
                    maxim=x;
           //     printf("%d ",x);
            }
        }
}
void Solve()
{
    long long nr=0;
    long p=1,j;
  /*  while(s>0)
    {
        while(v[p]>0 && s>0)
        {
            if(s<p)
            {
                s=0;
                break;
            }
            ++nr;
            s-=p;
            --v[p];
        }
        ++p;
    }*/
    while(s>0 && p<=maxim)
    {
        j=1;
        while(s>0 && j<=v[p])
        {
            if(s<p)
            {
                s=0;
                break;
            }
            s-=p;
            j++;
            nr++;
        }
        p++;
    }
    printf("%lld",nr);
}
int main()
{
    Read();
    Solve();
    return 0;
}
