#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin=freopen("checkin.in","r",stdin);
FILE *fout=freopen("checkin.out","w",stdout);
long N, K, P, Max,  A[1001], B[1001], V[1001];

void Read()
{
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%d%d", &A[i], &B[i]);
    }
    scanf("%d%d", &P, &K);
}


void Solve()
{
    long st, dr, m;
    for(int i = 1 ; i <= N ; ++i )
        if( A[i] * K + B[i] > Max )
            Max = A[i] * K + B[i];
    st = 1 , dr = Max;
    while(st < dr )
    {
        m = (st + dr) / 2;
        long Sum = 0, ok = 0;
        for(int i = 1 ; i <= N ; ++i )
        {
            if( m < B[i] + A[i] )
                V[i] = -1;
         //   else if( m - B[i] < A[i] )
         //       V[i] = -1;
            else
                V[i] = ( m - B[i] ) / A[i];
        }
        sort( V + 1 , V + N + 1 );
        for(int i = N ; i > N - min(P, N) ; --i )
            if( V[i] > 0 )
            {
                Sum += V[i];
                ok = 1;
                if( Sum >= K )
                    break;
            }
        if( Sum >= K  )
            dr = m;
        else
            st = 1 + m;
    }
    bool ok = 1;
    printf("%d", st);
}

int main()
{
    Read();
    if( K == 0 )
    {
        int Min = 100000;
        for(int i = 1 ; i <= N ; ++i )
            if( Min > B[i] )
                Min = B[i];
        printf("%d",Min);
        return 0;
    }
    Solve();
    return 0;
}
