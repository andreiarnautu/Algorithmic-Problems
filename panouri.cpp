#include <cstdio>
using namespace std;
FILE *f=freopen("panouri.in","r",stdin);
FILE *g=freopen("panouri.out","w",stdout);
int n,t,v[15001],st=1, fin=1,w[1001],fr[15001],nr=0,minim=20000;
int main()
{
    int i,j,x;
    scanf("%d%d",&n,&t);
    for(i=1;i<=n;i++)
        scanf("%d",&v[i]);
    for(i=1;i<=t;i++)
    {
        scanf("%d",&x);
        w[x]=1;
    }
    if(w[v[st]]==1)
    {
        fr[v[st]]=1;
        nr=1;
    }
    while(fin<n && nr<t)
    {
        fin++;
        if(w[v[fin]]==1)
        {
            if(fr[v[fin]]==0)
                ++nr;
            ++fr[v[fin]];
        }
    }
    if(nr<t)
    {
        printf("-1 \n");
        return 0;
    }
    while(w[v[st]]==0 || fr[v[st]]>1)
        --fr[v[++st]];
    minim=20000;
    if(minim>fin-st)
        minim=fin-st;
    for(fin=fin+1;fin<=n;++fin)
    {
        if(w[v[fin]]==1)
            fr[v[fin]]++;
        while(w[v[st]]==0 || fr[v[st]]>1)
            --fr[v[st++]];
        if(minim>fin-st)
            minim=fin-st;
    }
    printf("%d\n",minim);
    return 0;
}
