#include <cstdio>
using namespace std;
FILE *fin=freopen("nice.in","r",stdin);
FILE *fout=freopen("nice.out","w",stdout);
long long putere(int i)
{
    long long x=1;
    for(int j=0;j<i;j++)
        x*=3;
    return x;
}
int main()
{
    int n;
    long long s=0;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        printf("%d ",putere(i));
        s+=putere(i);
    }
    printf("\n%d",s+1);
    return 0;
}
