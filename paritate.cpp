#include <cstring>
#include <cstdio>
#include <fstream>
#define Dim 480013

using namespace std;

ifstream in("paritate.in");
ofstream out("paritate.out");
FILE *fin=freopen("paritate.in","r",stdin);
FILE *fout=freopen("paritate.out","w",stdout);

char S[8];
short Cod[Dim / 8];
int nr, y;
bool ok = 1, Corect[Dim / 8];
int oki = 1 , cnt = 0, p = 1;

void Check()
{
    ++nr;
    oki = 1 , cnt = 0 , p = 1;
    for( y = 7 ; y > 0 ; --y )
    {
        Cod[nr] += ( S[y] - 48 ) * p;
        p *= 2;

        if( S[y] == '1' )
            ++cnt;
    }

    if( ( cnt % 2 == 0 && S[0] == '1' ) || ( cnt % 2 == 1 && S[0] == '0' ) )
    {
        ok = 0;
        oki = 0;
    }

    Corect[nr] = oki;

}

int main()
{

    int len, i , j;
    S[0] = '0';

    while( S[0] != NULL )
    {
        in.get(S, 9);
        if( S[0] == NULL )
            break;
        Check();
    }

    if( !ok )
    {
        printf("NU\n");
        for( i = 1 ; i <= nr ; ++i )
            if( !Corect[i] )
                printf("%d ",i - 1);
    }
    else
    {
        char c;
        printf("DA\n");
        for( i = 1 ; i <= nr ; ++i )
        {
            c = Cod[i];
            printf("%c", c);
        }
    }
    return 0;
}
