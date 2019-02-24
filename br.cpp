#include <cstdio>
using namespace std;
FILE *fin=freopen("br.in","r",stdin);
FILE *fout=freopen("br.out","w",stdout);
int N, T;
long V[30020];
void Read()
{
    int x;
    scanf("%d%d",&N,&T);
    for(int i=1; i<=N ; ++i)
    {
        scanf("%d",&x);
        V[i] = V[i-1] + x;
    }
    for(int i=N+1; i<=N*2 ; ++i)
        V[i] = V[N] + V[i-N];
}
void Solve()
{
    int ok, st, dr, Nr, Sum, m;
    for(int i=1; i<=T ; ++i)
    {
        scanf("%d%d",&Nr,&Sum);
        st=Nr;
        dr=Nr+N;
        if( Sum >= V[N] )
            printf("%d\n",N);
        else if( V[Nr]- V[Nr-1] > Sum)
            printf("0\n");
        else
        {
            ok=0;
            while(st+1<dr)
            {
                m=(st+dr)/2;
                //printf("%d %d\n",st,dr);
                if( V[m]-V[Nr-1]<=Sum && V[m+1]-V[Nr-1]>Sum )
                {
                    ok=1;
                    break;
                }
                if( V[m]-V[Nr-1]>=Sum )
                    dr=m;
                else
                    st=m;
            }
            if(ok)
                printf("%d\n",m-Nr+1);
            else
                printf("0\n");
        }
    }
}
int main()
{
    Read();
    Solve();
    return 0;
}
