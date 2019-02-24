#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin=freopen("jucarii.in","r",stdin);
FILE *fout=freopen("jucarii.out","w",stdout);
int v[20],nr=1,l[20],n,k,p;
int verifica()
{
    int i,j,maxim=0;
    l[n-1]=1;
    for(i=n-2;i>=0;i--)
    {
        maxim=0;
        for(j=i+1;j<n;j++)
            if(v[i]<v[j] && l[j]>maxim)
                maxim=l[j];
        l[i]=maxim+1;
        if(l[i]>=k)
            return 1;
    }
    return 0;
}
int main()
{
    int i;
    scanf("%d%d%d",&n,&k,&p);
    for(i=0;i<n;i++)
        v[i]=i+1;
    while(nr<p)
    {
        next_permutation(v,v+n);
        if(verifica())
            ++nr;
    }
    for(i=0;i<n;i++)
        printf("%d ",v[i]);
    return 0;
}
