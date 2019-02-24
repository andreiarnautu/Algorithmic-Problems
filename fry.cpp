#include <cstdio>
using namespace std;
FILE *fin=freopen("fry.in","r",stdin);
FILE *fout=freopen("fry.out","w",stdout);
int n,k;
int v[1001];
void Read()
{
    scanf("%d%d",&n,&k);
}
void Solve()
{
    int x;
    if(n<=k)
    {
        printf("2\n");
        for(int i=1;i<=2;i++)
        {
            printf("%d ",i);
            for(int j=1;j<=n;j++)
                printf("%d ",j);
            printf("\n");
        }
        return;
    }
    if((n<<1)%k==0)
    {
        x=(n<<1)/k;
        printf("%d",x);
    }
    else
    {
        x=(n<<1)/k+1;
        printf("%d",x);
    }
    int q=0;
    for(int i=1;i<=2*n;i++)
    {
        if(q%k==0)
            printf("\n%d ",q/k+1);
        if(i<=n)
            printf("%d ",i);
        else
            printf("%d ",i-n);
        ++q;
    }
}
int main()
{
    Read();
    Solve();
    return 0;
}
