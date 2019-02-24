#include <cstdio>
#define Dim 500013
using namespace std;
FILE *fin=freopen("numere11.in","r",stdin);
FILE *fout=freopen("numere11.out","w",stdout);
int N;
bool Viz[Dim];

void Ciur()
{
    int i , j;
    for( i = 3 ; i <= N ; i += ( 1 << 1 ) )
        if( !Viz[i] )
            for( j = i * i ; j <= N ; j += ( i << 1 ) )
                Viz[j] = 1;
}

void Solve()
{

}

int main()
{
    scanf("%d", &N);
    Ciur();
    Solve();
}
