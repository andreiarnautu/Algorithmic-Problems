#include <cstdio>
#include <bitset>
#define MaxN 2003

using namespace std;

FILE *fin=freopen("intersectii.in","r",stdin);
FILE *fout=freopen("intersectii.out","w",stdout);

int F[2 * MaxN], N, W, H, r, query;
bitset <MaxN> A[MaxN];

void Read()
{
    scanf("%d%d%d", &W, &H, &N);
}

void Precalculate()
{
    int i, j, x, l;

    for( i = 1 ; i < W ; ++i )
        for( j = 1 ; j < H ; ++j )
            if( !A[i][j] )
            {
                for( l = 1 ; l * i < W && l * j < H ; ++l )
                {
                    ++F[l * (i + j - 1)];
                    A[i * l][j * l] = 1;
                }
            }
}

void Answer()
{
    scanf("%d", &query);
    printf("%d\n", F[query] * 4 );
}

int main()
{
    Read();
    Precalculate();
    for(int i = 1 ; i <= N ; ++i )
        Answer();
    return 0;
}
