#include <cstdio>
using namespace std;
FILE *fin=freopen("excursie1.in","r",stdin);
FILE *fout=freopen("excursie1.out","w",stdout);
int N;
bool viz[30001];
void Read()
{
    scanf("%d",&N);
}
void Solve()
{
    if(N<5)
    {
        printf("NU\n");
        return;
    }
    if(N%3==1)
    {
        printf("NU\n");
        return;
    }
    printf("DA\n");
    long long S,s;
    S=N*(N+1)/6;
    s=0;
    for(int k=0; k<3 ; ++k)
    {
        s=0;
        for(int i=N; i>0 ; --i)
            if(!viz[i] && s+i<=S)
            {
                printf("%d ",i);
                s+=i;
                viz[i]=1;
                if(s==S)
                    break;
            }
        printf("\n");
    }
}
int main()
{
    Read();
    Solve();
}
