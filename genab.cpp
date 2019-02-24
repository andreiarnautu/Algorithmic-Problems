#include <cstdio>
using namespace std;
FILE *fin=freopen("genab.in","r",stdin);
FILE *fout=freopen("genab.out","w",stdout);
int v[21];

void generaresub(int n)
{
    int g=1,i,j,ok;

    for(i=0;i<n;i++)
        printf("a");
    printf("\n");
    while(g)
    {
        g=0;
        ok=0;
        for(i=n-1;i>=0;i--)
            if(v[i]==0)
            {
                g=1;
                break;
            }
        if(g==1)
        {
            v[i]=1;
            for(j=i+1;j<n;j++)
                v[j]=0;
            for(j=0;j<n-1;j++)
                if(v[j]==1 && v[j+1]==1)
                    ok=1;
            if(ok==0)
                {
                    for(j=0;j<n;j++)
                    {
                        if(v[j]==1)
                            printf("b");
                        else
                            printf("a");
                    }
                    printf("\n");
                }
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    generaresub(n);
    return 0;
}
