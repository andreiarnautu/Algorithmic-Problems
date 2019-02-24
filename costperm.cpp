#include <cstdio>
#include <algorithm>
#include <vector>
#define Dim 100003
#define zeros(x) ( (x ^ (x - 1)) & x )
using namespace std;

FILE *fin=freopen("costperm.in","r",stdin);
FILE *fout=freopen("costperm.out","w",stdout);

vector <int> Pos(Dim), AIB(Dim), V(Dim), Aux(Dim), Val(Dim);
vector <int>::iterator it;
int n;


void Read()
{
    scanf("%d", &n);
    for(int i = 1; i <= n ; ++i)
    {
        scanf("%d", &V[i]);
        Aux[i] = V[i];
    }

    sort(Aux.begin() + 1, Aux.begin() + n + 1);

    for(int i = 1; i <= n ; ++i)
    {
        it = upper_bound(Aux.begin(), Aux.begin() + n + 1, V[i]);
        V[i] = it - Aux.begin() - 1;
        Pos[V[i]] = i;
    }

    for(int i = 1; i <= n ; ++i)
        Val[i] = Aux[i];
}

void Add(int x, int quantity)
{
    int i;

    for (i = x; i <= n; i += zeros(i))
        AIB[i] += quantity;
}

int Compute(int x)
{
    int i, ret = 0;

    for (i = x; i > 0; i -= zeros(i))
        ret += AIB[i];
    return ret;
}

void Solve()
{
    long long int sol = 0;

    for(int i = n; i > 0 ; --i)
    {
        sol += 1LL * Compute(Pos[i]) * Val[i];
        Add(Pos[i], 1);
    }

    printf("%lld", sol);
}

int main()
{
    Read();
    Solve();
    return 0;
}
