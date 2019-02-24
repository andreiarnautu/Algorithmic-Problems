#include <cstdio>
#include <vector>
#define MOD 100003
using namespace std;
FILE *fin=freopen("hashuri.in","r",stdin);
FILE *fout=freopen("hashuri.out","w",stdout);

vector < vector<int> > HASH(MOD);
vector <int>::iterator it;

int main()
{
    int n, op, x, aux;
    for(scanf("%d", &n); n > 0 ; --n)
    {
        scanf("%d%d", &op, &x);

        if( op == 1 )
        {
            aux = x;
            x %= MOD;
            for(it = HASH[x].begin(); it != HASH[x].end() && *it != aux; ++it);
            if( it == HASH[x].end() )
                HASH[x].push_back(aux);
        }

        else if( op == 2 )
        {
            aux = x;
            x %= MOD;
            for(it = HASH[x].begin(); it != HASH[x].end() && *it != aux; ++it);
            if( it != HASH[x].end() )
                HASH[x].erase(it);
        }

        else
        {
            aux = x;
            x %= MOD;
            for(it = HASH[x].begin(); it != HASH[x].end() && *it != aux; ++it);
            if( it != HASH[x].end() )
                printf("1\n");
            else
                printf("0\n");
        }
    }
}
