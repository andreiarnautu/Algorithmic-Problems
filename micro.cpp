#include <cstdio>
#include <set>
#include <algorithm>
#define DIM 100010
#define PII pair<long long int, int>
#define mp make_pair
using namespace std;
FILE *fin=freopen("micro.in","r",stdin);
FILE *fout=freopen("micro.out","w",stdout);

int p[DIM], cp[DIM], nr[DIM], d[DIM], cd[DIM];
int n;
multiset < PII > ms;
multiset < PII >::iterator it;

void Read()
{
    int i;
    scanf("%d", &n);

    for(i = 0; i < n; ++i)
        scanf("%d %d %d ", &p[i], &cp[i], &nr[i]);
    for(i = 0; i < n - 1;  ++i)
        scanf("%d %d ", &d[i], &cd[i]);
}

void Solve()
{
    long long int stacked_cost = 0, sol = 0, cnt = 0, no;
    int i;

    for(i = 0; i < n; ++i)
    {
        ms.insert( mp( cp[i] - stacked_cost, p[i] ) );

        cnt += p[i];

        while( !ms.empty() && nr[i] > 0 )
        {
            it = ms.begin();
            PII f_pair = *it;
            no = min( nr[i], f_pair.second );

            f_pair.second -= no;
            nr[i] -= no;

            sol += 1LL * no * ( stacked_cost + f_pair.first );

            ms.erase(it);

            if( f_pair.second > 0 )
                ms.insert(f_pair);

            cnt -= no;
        }

        if( nr[i] > 0 )
        {
            printf("-1");
            return;
        }

        if( i != n - 1 )
        {
            stacked_cost += cd[i];

            while( cnt > d[i] )
            {
                it = ms.end(), --it;
                PII l_pair = *it;
                ms.erase(it);

                no = cnt - d[i];
                cnt -= l_pair.second;

                if( l_pair.second > no )
                {
                    l_pair.second -= (int) no;
                    ms.insert(l_pair);
                    cnt += l_pair.second;
                }
            }
        }
    }

    printf("%lld", sol);
}

int main()
{
    Read();
    Solve();
    return 0;
}

