#include <cstdio>
using namespace std;
FILE *fin=freopen("carti1.in","r",stdin);
FILE *fout=freopen("carti1.out","w",stdout);
bool viz[100001];
int main()
{
    long n,i,nr=0,x;
    scanf("%d",&n);
    viz[0]=1;
    for(i=0;i<n;i++)
    {
        scanf("%d",&x);
        ++viz[x];
        if(!viz[x-1])
            ++nr;
    }
    printf("%d",nr);
    return 0;
}
