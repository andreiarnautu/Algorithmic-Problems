#include <cstdio>
#include <cstring>

using namespace std;

FILE *fin=freopen("dmin2.in","r",stdin);
FILE *fout=freopen("dmin2.out","w",stdout);

int N, M, G[300003], ok[300003];
char s[15];

int main()
{
    scanf("%d%d", &N, &M);

    int x, y, aux;
    long long int  S = 0;
    if( N <= 4 )
    {
        printf("0");
        return 0;
    }

    getchar();

    for(int i = 1 ; i <= M ; ++i )
    {
        gets(s);
        aux = 0;
        for(int j = 0 ; j < strlen(s) ; ++j )
        {
            if( s[j] == ' ' )
            {
                x = aux;
                aux = 0;
            }
            else
                aux = aux * 10 + s[j] - 48;
        }

        y = aux;

        if( x == 1 || x == N )
            ok[y] = 1;
        else if( y == 1 || y == N )
            ok[x] = 1;
        else
        {
            ++G[x];
            ++G[y];
        }
    }

    for(int i = 2 ; i < N ; ++i )
    {
        if( !ok[i] )
            S += 2;
        S += ( N - 3 - G[i] );
    }

    S /= 2;

    printf("%lld", S);

}
