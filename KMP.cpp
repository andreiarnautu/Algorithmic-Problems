#include <cstring>
#include <cstdio>

#define MAXN 2000003

using namespace std;

FILE *fin=freopen("strmatch.in","r",stdin);
FILE *fout=freopen("strmatch.out","w",stdout);

char X[MAXN], Y[MAXN];
int Pi[MAXN], d[MAXN];
int i, K, N, M;

void constructie_pi() //constructia pi-ului
{
    N = strlen(X)-1;
    K = 0;     // iteratorul K care ne ajuta la contructia lui Pi
    Pi[1] = 0; // Pi[i] < i => Pi[1] = 0
    for (i = 2; i <= N; ++i){
        while (K > 0 && X[i] != X[K+1]) // cat timp prefixul nu este nul si literele
            K = Pi[K];                  // nu coincid sar din K in Pi[K]
        if (X[i] == X[K+1]) K = K + 1;  // daca literele coicid
        Pi[i] = K;
    }
}

int main()
{

    fgets(X, sizeof(X), stdin);
    fgets(Y, sizeof(Y), stdin);

    //printf("%s %s", X, Y);
    //X[0] = ' '; Y[0] = ' ';
    X[strlen(X)-1] = Y[strlen(Y)-1] = 0;

    M = strlen(Y)-1;
    constructie_pi();
    K = 0;
    for (i = 1; i <= M; ++i){
        while (K > 0 && Y[i] != X[K+1]) // cat timp prefixul nu este nul si literele
            K = Pi[K];                  // nu coincid sar din K in Pi[K]
        if (Y[i] == X[K+1]) K = K + 1;  // daca literele coincid
        d[i] = K;
    }

    int nr = 0;

    for (i = 1;  i <= M; ++i)
        if (d[i] == N)
            ++nr;

    printf("%d\n",nr);
    if( nr > 1000 )
        nr = 1000;

    for (i = 1;  i <= M && nr ; ++i)
        if (d[i] == N)              // daca d[i] == N inseamna ca intreg sirul X coincide
        {
            printf("%d ", i - N);   // cu sufixul lui Yi
            --nr;
        }
    return 0;
}
