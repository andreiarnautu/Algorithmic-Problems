#include <cstdio>
#include <deque>

using namespace std;

FILE *fin=freopen("deque.in","r",stdin);
FILE *fout=freopen("deque.out","w",stdout);

deque <int> d;
int n, k, v[5000005];
long long int Sum;

int main()
{
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++i )
    {
        scanf("%d", &v[i]);
        while( !d.empty() && v[d.back()] > v[i] )
            {
                d.pop_back();
            }
        d.push_back(i);

        if( d[0] + k <= i )
            d.pop_front();

        if( i >= k )
            Sum = 1ll * ( Sum + v[d[0]] );
    }

    printf("%lld", Sum);

    return 0;
}
