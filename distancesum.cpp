// BRUTE FORCE
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin=freopen("distancesum.in","r",stdin);
FILE *fout=freopen("distancesum.out","w",stdout);

int N, M;

struct punct{int x, y;};
punct V[100002], P;

long long int Dsum;


void Calculate()
{
    Dsum = 0;
    for(int i = 1 ; i <= N ; ++i )
    {
        Dsum += max( abs( V[i].x - P.x ) , abs( V[i].y - P.y ) );
    }
    printf("%lld\n", Dsum);
}

int main()
{
    scanf("%d%d", &N, &M);
    for(int i = 1 ; i <= N ; ++i )
        scanf("%d%d", &V[i].x, &V[i].y);
    for(int i = 1 ; i <= M ; ++i)
    {
        scanf("%d%d", &P.x, &P.y);
        Calculate();
    }
}
