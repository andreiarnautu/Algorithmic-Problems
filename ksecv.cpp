#include <cstdio>
#include <queue>
#define DIM 100010
using namespace std;
FILE *fin=freopen("ksecv.in","r",stdin);
FILE *fout=freopen("ksecv.out","w",stdout);

int V[DIM];
priority_queue <int, vector<int>, greater<int> > heap;
int n, k, best, first, last, pos = 1;

void Read()
{
    scanf("%d %d ", &n, &k);
    for(int i = 1; i <= n; ++i)
        scanf("%d ", &V[i]);
}

void Solve()
{
    int i, val = -1;

    for(i = 1; i <= n; ++i)
        if( val < V[i] )
        {
            while( !heap.empty() && V[i] >= heap.top() )
                heap.pop();

            while( pos <= n )
            {
                if( V[pos] <= V[i] )
                    ++pos;
                else if( heap.size() < k )
                {
                    heap.push( V[pos] ); ++pos;
                }
                else
                    break;
            }

            if( best < pos - i )
            {
                best = pos - i;
                first = i;
                last = pos - 1;
            }

            val = V[i];
            //printf("%d %d %d\n", val, i, pos);
        }

    printf("%d %d", first, last);
}

int main()
{
    Read();
    Solve();
    return 0;
}
