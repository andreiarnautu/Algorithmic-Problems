#include <cstdio>
using namespace std;
FILE *fin=freopen("bal.in","r",stdin);
FILE *fout=freopen("bal.out","w",stdout);
int M, N, F[1000000], B[1000000];
void Read()
{
    int st,dr;
    scanf("%d%d",&N,&M);
    for(int i=0; i<N ; ++i)
    {
        scanf("%d%d",&st,&dr);
        ++F[st];
        --F[dr+1];
    }
    for(int i=0; i<M ; ++i)
    {
        scanf("%d%d",&st,&dr);
        ++B[st];
        --B[dr+1];
    }
}
int minim(int a, int b)
{
    if(a<=b)
        return a;
    return b;
}
void Solve()
{
    int b=0,f=0,Max=0;
    for(int i=1; i<=1000000 ; ++i)
    {
        b+=B[i];
        f+=F[i];
        if(minim(f,b)>Max)
            Max = minim(f,b);
    }
    printf("%d",Max);
}
int main()
{
    Read();
    Solve();
    return 0;
}
