#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

FILE *fin=freopen("nrtri.in","r",stdin);
FILE *fout=freopen("nrtri.out","w",stdout);

vector <int> v;
int n, cnt;


void Read()
{
    int i, x;
    scanf("%d", &n);
    for(i = 0 ; i < n ; ++i)
    {
        scanf("%d", &x);
        v.push_back(x);
    }

    sort(v.begin(), v.end());
}

void Solve()
{
    int i, j, sum, p2, pos, aux;


    for(p2 = 1; p2 < n ; p2 <<= 1);

    for(i = 0; i < n - 2 ; ++i)
        for(j = i + 1 ; j < n - 1 ; ++j )
        {
            sum = v[i] + v[j], aux = p2, pos = 0;

            for(; aux > 0; aux >>= 1 )
                if( pos + aux < n && v[pos + aux] <= sum)
                    pos += aux;
            cnt += pos - j;
        }

    printf("%d", cnt);
}

int main()
{
    Read();
    Solve();
}
