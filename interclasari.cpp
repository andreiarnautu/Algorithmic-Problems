// How about a coding trick?
#include <cstdio>
#include <queue>
using namespace std;
FILE *fin=freopen("interclasari.in","r",stdin);
FILE *fout=freopen("interclasari.out","w",stdout);

priority_queue < int, vector<int>, greater<int> > heap;
int n;

int main()
{
    int n, k, i, x, nr = 0;

    for(scanf("%d", &n); n; --n)
    {
        scanf("%d", &k);
        for(i = 1; i <= k; ++i)
        {
            scanf("%d", &x);
            heap.push(x); ++nr;
        }
    }
    printf("%d\n", nr);

    for(; nr; --nr)
    {
        printf("%d ", heap.top()); heap.pop();
    }
    return 0;
}
