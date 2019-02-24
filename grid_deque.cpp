#include <cstdio>
#include <vector>
#include <deque>
using namespace std;
FILE *fin=freopen("grid.in","r",stdin);
FILE *fout=freopen("grid.out","w",stdout);
deque <int> D1;
deque <int> D2;
deque <int> D3;
int N , K;

void Read()
{
    scanf("%d%d", &N, &K);
    for(int i = 1 ; i <= N ; ++i )
        D1.push_back(i);
    for(int i = N + 1 ; i <= 2 * N ; ++i )
        D2.push_back(i);
    for(int i = 2 * N + 1 ; i <= 3 * N ; ++i )
        D3.push_back(i);
}

void Solve()
{
    int a, b, c , d, x;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    if( a == 0 )
    {
        x = D1[b];
        D1.erase(D1.begin() + b);
    }
    else if( a == 1 )
    {
        x = D2[b];
        D2.erase(D2.begin() + b);
    }
    else
    {
        x = D3[b];
        D3.erase(D3.begin() + b);
    }
    if( c == 0 )
        D1.insert(D1.begin() + d, x);
    else if ( c == 1 )
        D2.insert(D2.begin() + d, x);
    else if ( c == 2 )
        D3.insert(D3.begin() + d, x);
}

int main()
{
    Read();
    for(int i = 1 ; i <= K ; ++i )
        Solve();
    int k;
    k = D1.size();
    for(int i = 0 ; i < k ; ++i )
        printf("%d ", D1[i]);
    printf("\n");
    k = D2.size();
    for(int i = 0 ; i < k ; ++i )
        printf("%d ", D2[i]);
    printf("\n");
    k = D3.size();
    for(int i = 0 ; i < k ; ++i )
        printf("%d ", D3[i]);
    return 0;
}
