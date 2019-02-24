#include <cstdio>
using namespace std;
FILE *fin=freopen("miere.in","r",stdin);
FILE *fout=freopen("miere.out","w",stdout);

int M, N, Max;
long long int V[50001];

void Read()
{
    long long int x;
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%lld", &x);
        V[i] = V[i - 1] + x;
    }
}

void Solve()
{
    long long x, st, dr, m;
    scanf("%d", &M);
    for(int i = 1 ; i <= M ; ++i )
    {
        scanf("%lld", &x);
        st = 1;
        dr = N + 1;
        while( st + 1 < dr )
        {
            m = (st + dr) / 2;
            if( V[m] + (i - 1) * m < x && x < V[m + 1] + (i - 1) * (m + 1) )
            {
                st = m;
                break;
            }
            if( V[m] + (i - 1) * m == x )
            {
                st = m;
                break;
            }
            else if( x < V[m] + (i - 1) * m )
                dr = m;
            else
                st = m;
        }
        Max = st;
        printf("%d\n",st);
    }
}

int main()
{
    Read();
    Solve();
    return 0;
}
