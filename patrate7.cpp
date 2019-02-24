#include <cstdio>
using namespace std;
FILE *fin=freopen("patrate7.in","r",stdin);
FILE *fout=freopen("patrate7.out","w",stdout);
int M, N;
long long int Sol;
int main()
{
    int x, b;
    scanf("%d%d", &N, &M);
    scanf("%d", &x);
    Sol = ( 1 << (x - 1));
    for(int i = 2 ; i <= M ; ++i )
    {
        scanf("%d", &b);
        Sol += ( 1 << (b - 1));
    }
    printf("%I64d\n", Sol);
    b = ( 1 << (N - 1));
    long long int Dim = 1, C, Col, Lin;
    while( Dim * Dim < b )
        ++Dim;
    C = ( (Sol >> (x)) << (x - 1) ) + ( Sol & ( (1 << (x - 1)) - 1) );
    Col = C / Dim + 1;
    Lin = C % Dim + 1;
    printf("%lld %lld\n", Lin, Col);
    return 0;
}
