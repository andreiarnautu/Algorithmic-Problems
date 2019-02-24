#include <cstdio>
#define Inf 1000000000
using namespace std;
FILE *fin=freopen("energii.in","r",stdin);
FILE *fout=freopen("energii.out","w",stdout);
int Best[5010], N , W;
struct{int E, C;} V[1001];


int main()
{
    scanf("%d%d", &N, &W);
    for(int i = 1 ; i <= N ; ++i )
        scanf("%d%d", &V[i].E, &V[i].C);
    for(int i = 1 ; i <= W ; ++i )
        Best[i] = Inf;
    for(int i = 1 ; i <= N ; ++i )
        for(int j = W ; j >= 0  ; --j )
            if( Best[j] != Inf )
            {
                if( j + V[i].E >= W )
                {
                    if( Best[W] > Best[j] + V[i].C )
                        Best[W] = Best[j] + V[i].C;
                }
                if( j + V[i].E < W )
                {
                    if(Best[j + V[i].E] > Best[j] + V[i].C )
                        Best[j + V[i].E] = Best[j] + V[i].C;
                }
            }

    if( Best[W] == Inf )
        printf("-1");
    else
        printf("%d", Best[W]);
    return 0;
}
