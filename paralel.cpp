#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin=freopen("paralel.in","r",stdin);
FILE *fout=freopen("paralel.out","w",stdout);
int n;
struct {int x,y;} C[501];
float v[250001],a,b;
long long k;
int main()
{
    int i,j;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d%d",&C[i].x,&C[i].y);
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
        {
            a=(float)(C[i].x+C[j].x)/2;
          //  printf("%.3f ",a);
            b=(float)(C[i].y+C[j].y)/2;
            a=a*1000+b;
          //  printf("%.3f ",a);
            v[++k]=a;
        }
    sort(v,v+k);
    long long nr=1,t=0;
    for(i=1;i<k;i++)
    {
      //  printf("%d ",nr);
        if(v[i]==v[i-1])
        {
            if(i==n-1)
            {
                ++nr;
                t+=nr*(nr-1)/2;
            }
            else
                ++nr;
        }
        else
        {
            t+=nr*(nr-1)/2;
            nr=1;
        }
    }
    printf("%lld",t);
    return 0;
}
