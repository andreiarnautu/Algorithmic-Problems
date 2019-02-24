#include <cstdio>
#include <algorithm>
#include <deque>
#define Nmax 1010
using namespace std;

FILE *fin=freopen("cai.in","r",stdin);
FILE *fout=freopen("cai.out","w",stdout);

deque <long long int> D;

long long int N, A[Nmax], B[Nmax], T;


int cmp(long long int a, long long int b)
{
    return (a > b);
}

void Run()
{
    scanf("%lld", &N);
    for(int i = 1 ; i <= N ; ++i )
        scanf("%lld", &A[i]);
    for(int i = 1 ; i <= N ; ++i )
        scanf("%lld", &B[i]);

    sort( A + 1 , A + N + 1, cmp);
    sort( B + 1 , B + N + 1, cmp);

    for(int i = 1 ; i <= N ; ++i )
        D.push_back( B[i] );
    int pos;
    pos = 1;

    while( D[0] < A[pos] && pos <= N )
    {
        B[pos] = D[0];
        ++pos;
        D.pop_front();
    }

    for(int i = N ; i >= pos ; --i )
    {
        if( D[D.size() - 1] < A[i] )
        {
            B[i] = D[D.size() - 1];
            D.pop_back();
        }
        else
        {
            B[i] = D[0];
            D.pop_front();
        }
        while( D[0] < A[pos] && pos < i  )
        {
            B[pos] = D[0];
            ++pos;
            D.pop_front();
        }
    }
    long long int Val = 0;
    for(int i = 1 ; i <= N ; ++i )
    {
        if( A[i] < B[i] )
            Val -= 200;
        else if( A[i] > B[i] )
            Val += 200;
    }
    printf("%lld\n", Val);
}

int main()
{
    scanf("%d", &T);
    for(int i = 1 ; i <= T; ++i )
        Run();
}
