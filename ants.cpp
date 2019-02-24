#include <cstdio>
using namespace std;
FILE *fin=freopen("ants.in","r",stdin);
FILE *fout=freopen("ants.out","w",stdout);
long N;
long long D[100001],F[100001],st=1,dr=1;
void Read()
{
    scanf("%d",&N);
    for(long i=0; i<N ; ++i)
    {
        scanf("%d%d",&D[i],&F[i]);
        if(F[i]>dr)
            dr=F[i];
    }
}
int True(int k)
{
    long long R=0,x;
    for(long i=0; i<N-1 ; ++i)
    {
        x=R+F[i];
        if(x<k)
            R=x-k-(D[i+1]-D[i]);
        else
        {
            R=x-k-(D[i+1]-D[i]);
            if(R<0)
                R=0;
        }
    }
    if(F[N-1]+R>=k)
        return 1;
    return 0;
}
void Solve()
{
    long long m;
    while(st<dr)
    {
        m=(st+dr+1)/2;
        if(True(m))
            st=m;
        else
            dr=m-1;
    }
    printf("%d",st);
}
int main()
{
    Read();
    Solve();
    return 0;
}
