#include <cstdio>
#include <vector>
using namespace std;

FILE *fin=freopen("mincinosi.in","r",stdin);
FILE *fout=freopen("mincinosi.out","w",stdout);

vector <int> a;
vector <int> F(1000003);
vector <int>::iterator it;
int n, val, best;

void Read()
{
    int i, x;

    scanf("%d", &n);
    for(i = 0 ; i < n ; ++i)
    {
        scanf("%d", &x);
        a.push_back(x);
        ++F[x];
    }
}

void Solve()
{
    int i;

    for(i = 0 ; i < n ; ++i)
    {
        if( F[i] && F[i] == n - i )
            if( best < F[i] )
            {
                best = F[i];
                val =  i;
                break;
            }
    }

    printf("%d\n",best);
    for(it = a.begin() ; it <= a.end() ; ++it)
        if( *it == val )
            printf("%d\n", it - a.begin() + 1);
}

int main()
{
    Read();
    Solve();
}
