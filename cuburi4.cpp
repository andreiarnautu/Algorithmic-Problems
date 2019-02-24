#include <cstdio>
#include <cstring>
using namespace std;
FILE *fin=freopen("cuburi4.in","r",stdin);
FILE *fout=freopen("cuburi4.out","w",stdout);

int F[60000], best, C[7], D[5], OK[60000], n, V[50], k;

void Check()
{
    int i, nr = 0, p = 1;
    for(i = 1; i <= 4; ++i, p *= 15)
        nr += D[i] * p;

    V[++k] = nr;
    if(!OK[nr])
    {
        ++F[nr];
        OK[nr] = 1;
    }
    if( F[nr] > best )
        best = F[nr];

    nr = 0, p = 1;
    for(i = 4; i > 0 ; --i, p *= 15)
        nr += D[i] * p;
    if(!OK[nr])
    {
        ++F[nr];
        OK[nr] = 1;
    }
    if( F[nr] > best )
        best = F[nr];
    V[++k] = nr;
}

void Do_Rotations()
{
    Check();

    int aux;
    for(int i = 1; i <= 3 ; ++i)
    {
        aux = D[1];
        for(int j = 1; j <= 3 ; ++j)
            D[j] = D[j + 1];
        D[4] = aux;
        Check();
    }
}

int main()
{
    char S[7];
    scanf("%d ", &n);
    for(int i = 1; i <= n ; ++i)
    {
        gets(S);
        for(int j = 1; j <= 6; ++j)
            C[j] = S[j - 1] - 'A';
        k = 0;

        D[1] = C[1], D[2] = C[5], D[3] = C[2], D[4] = C[3];
        Do_Rotations();

        D[1] = C[1], D[2] = C[4], D[3] = C[2], D[4] = C[6];
        Do_Rotations();

        D[1] = C[3], D[2] = C[4], D[3] = C[5], D[4] = C[6];
        Do_Rotations();

        for(int j = 1; j <= k ; ++j)
            OK[V[j]] = 0;
    }

    printf("%d", best);
}
