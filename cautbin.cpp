#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

FILE *fin=freopen("cautbin.in","r",stdin);
FILE *fout=freopen("cautbin.out","w",stdout);

vector <int> V;
vector <int>::iterator it;
int n;

void Read()
{
    int x;
    scanf("%d", &n);
    V.push_back(0);
    for(int i = 1; i <= n ; ++i)
    {
        scanf("%d", &x);
        V.push_back(x);
    }
}

void Solve()
{
    int m, op, val, pos;

    for(scanf("%d", &m); m > 0 ; --m)
    {
        scanf("%d %d", &op, &val);

        if( op == 0 )
        {
            it = upper_bound(V.begin() + 1, V.end(), val);
            pos = it - V.begin() - 1;
            if(pos <= n && pos > 0 && V[pos] == val)
                printf("%d\n", pos);
            else
                printf("-1\n");
        }

        else if( op == 1 )
        {
            it = upper_bound(V.begin(), V.end(), val);
            printf("%d\n", it - V.begin() - 1);
        }

        else
        {
            it = lower_bound(V.begin(), V.end(), val);
            printf("%d\n", it - V.begin());
        }
    }
}

int main()
{
    Read();
    Solve();
}
