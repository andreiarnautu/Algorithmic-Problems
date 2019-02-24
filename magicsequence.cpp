#include <cstdio>
#define max( a , b ) ((a > b) ? a : b)
#define min( a , b ) ((a > b) ? b : a)
#define Dim 20001

using namespace std;

FILE *fin=freopen("magicsequence.in","r",stdin);
FILE *fout=freopen("magicsequence.out","w",stdout);

int N, V[Dim];


void Run()
{
    int Max = 0, Min = 1000000009;
    scanf("%d", &N);

    for(int i = 1 ; i <= N ; ++i )
        scanf("%d", &V[i]);

    if( N == 1 )
    {
        printf("YES\n");
        return ;
    }

    if( V[N] > V[1] )
        printf("YES\n");
    else
        printf("NO\n");


}

int main()
{
    int T;
    scanf("%d", &T);
    for(int i = 1 ; i <= T ; ++i )
        Run();
}
