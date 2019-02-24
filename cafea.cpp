#include <cstdio>
using namespace std;
FILE *fin = freopen("cafea.in" , "r" , stdin );
FILE *fout = freopen("cafea.out" , "w" , stdout );
int N, K, A[10001];
struct{int first, last;} V[10003];


void Read()
{
    int p, t;
    scanf("%d%d", &N, &K);
    for(int i = 1 ; i <= K ; ++i )
    {
        scanf("%d%d", &p, &t);
        V[i].first = p;
        V[i].last = p + t;
    }
    p = 1;
    for(int i = 1 ; i < N ; ++i )

}

int main()
{
    Read();
}
