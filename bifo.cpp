// How about a coding trick?
#include <cstdio>
#include <cstring>
using namespace std;
FILE *fin=freopen("bifo.in","r",stdin);
FILE *fout=freopen("bifo.out","w",stdout);

short A[1000][110], nr = 2, Aux[110];
char S1[11000], S2[11000], Q[110];

void Read_and_Set()
{
    int len1, len2, i, t;

    scanf("%s", S1); scanf("%s", S2);
    len1 = strlen(S1), len2 = strlen(S2);

    while( len1 )
    {
        ++A[1][0];
        A[1][A[1][0]] = len1 % 10;
        len1 /= 10;
    }
    while( len2 )
    {
        ++A[2][0];
        A[2][A[2][0]] = len2 % 10;
        len2 /= 10;
    }

    while( A[nr][0] <= 100 )
    {
        ++nr;
        for(i = 1, t = 0; i <= A[nr - 1][0] || i <= A[nr - 2][0] || t; i++, t /= 10)
            A[nr][i] = (t += A[nr - 1][i] + A[nr - 2][i]) % 10;
        A[nr][0] = i - 1;
    }
}

inline bool comp(short int X[],short int Y[])
{
    int i;
    if( X[0] > Y[0] )
        return 1;
    if( X[0] < Y[0] )
        return 0;

    for(i = X[0]; i ; --i)
    {
        if( X[i] > Y[i] )
            return 1;
        if( X[i] < Y[i] )
            return 0;
    }
    return 0;
}

inline void scade(short int X[],short int Y[])
{
    int i, t = 0;
    for(i = 1; i <= X[0]; ++i)
        {
            X[i] -= ((i <= Y[0])? Y[i] : 0) + t;
            X[i] += (t = X[i] < 0) * 10;
        }
    for(; X[0] > 1 && !X[X[0]]; --X[0]);
}

void Query()
{
    int k, i, t, len;
    bool ok;

    scanf("%s", Q); len = strlen(Q);

    for(i = 0; i <= 105; ++i)
        Aux[i] = 0;

    for(i = len - 1; i >= 0; --i)
        Aux[len - i] = Q[i] - 48;
    Aux[0] = len;

    for(k = 1; k <= nr; ++k)
    {
        if( comp(Aux, A[k]) )
            {
                scade(Aux, A[k]);
            }
        else
            break;
    }
    while( k > 2 )
    {
        if( comp(Aux, A[k - 2]) )
            {
                scade(Aux, A[k - 2]);
                --k;
            }
        else
            {
                k -= 2;
            }
    }
    int nr = 0;
    for(i = Aux[0]; i ; --i)
            nr = nr * 10 + Aux[i];

    if( k == 1 )
    {
        printf("%c", S1[nr - 1]);
    }
    else
    {
        printf("%c", S2[nr - 1]);
    }
}

int main()
{
    int m;
    Read_and_Set();
    scanf("%d ", &m);
    for(; m > 0; --m)
    {
        Query();
    }
    return 0;
}
