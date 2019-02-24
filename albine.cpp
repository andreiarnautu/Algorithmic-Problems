#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin=freopen("albine.in","r",stdin);
FILE *fout=freopen("albine.out","w",stdout);
int M, N, A[1000];

void Change(int x)
{
    int i, t = 0;
    for( i = 1 ; i <= A[0] || t ; i++ , t /= 10 )
        A[i] = ( t += A[i] * x ) % 10;
    A[0] = i - 1;
}

int Calc(int x)
{
    int nr = 0, q;
    q = max( 0 , x - N );
    for(int i = q ; i <= x ; ++i )
        if( i <= M && x - i <= N )
            ++nr;
    return nr;
}

int main()
{
    int x;
    scanf("%d%d", &M, &N);
    A[0] = 1;
    A[1] = 1;
   // for(int i=1 ; i< M+N ; ++i)
  //      printf("%d\n",Calc(i));
    for(int i=1; i < M + N ; ++i )
    {
        x = Calc(i);
        Change(x);
    }
    for(int i = A[0]; i > 0 ; --i )
        printf("%d",A[i]);
    return 0;
}
