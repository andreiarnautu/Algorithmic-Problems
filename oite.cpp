#include <cstdio>
#include <vector>
#define DIM 6007
using namespace std;
FILE *fin=freopen("oite.in","r",stdin);
FILE *fout=freopen("oite.out","w",stdout);

vector <int> A[DIM];
int V[1<<10+3];
int C, L;

void Read()
{
    scanf("%d %d ", &C, &L);
    for(int i = 1; i <= C; ++i)
        scanf("%d ", &V[i]);
}

void Solve()
{
    long long int ans = 0;
    int i, j, sum, it;

    for(i = 1; i < C; ++i)
    {
        for(j = i + 1; j <= C; ++j)
        {
            sum = L - V[i] - V[j];
            if( sum > 0 )
                for(it = 0; it < A[sum % DIM].size(); ++it)
                    if( A[sum % DIM][it] == sum )
                        ++ans;
        }
        for(j = 1; j < i; ++j)
            A[(V[i] + V[j]) % DIM].push_back(V[i] +V[j]);
    }
    printf("%lld", ans);
}

int main()
{
    Read();
    Solve();
    return 0;
}
