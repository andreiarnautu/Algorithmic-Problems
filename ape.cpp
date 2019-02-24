// How about a coding trick?
#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin=freopen("ape.in","r",stdin);
FILE *fout=freopen("ape.out","w",stdout);

int xmin, xmax, ymin, ymax, x, y, p, A, sens;
char S[20200];

int main()
{
    int i;
    scanf("%d ", &p);
    gets(S);
    S[p] = S[0];
    for(i = 1; i <= p; ++i)
    {
        if( S[i - 1] == 'N' )
        {
            if( S[i] == 'E' )
                ++x;
            else if( S[i] == 'N' )
            {
                ++y, A -= (x + 1);
            }
            else if( S[i] == 'V' )
            {
                A -= (x + 1), --x;
            }
        }

        else if( S[i - 1] == 'S' )
        {
            if( S[i] == 'S' )
                A += x, --y;
            else if( S[i] == 'E' )
            {
                A += x, ++x;
            }
            else if( S[i] == 'V' )
                --x;
        }

        else if( S[i - 1] == 'E' )
        {
            if( S[i] == 'S' )
                --y;
            else if( S[i] == 'N' )
            {
                A -= (x + 1), ++y;
            }
            else if( S[i] == 'E' )
                ++x;
        }

        else
        {
            if( S[i] == 'N' )
                ++y;
            else if( S[i] == 'S' )
            {
                A += x, --y;
            }
            else if( S[i] == 'V' )
                --x;
        }
        xmax = max( x, xmax );
        xmin = min( x, xmin );
        ymax = max( y, ymax );
        ymin = min( y, ymin );

    }
    if( A < 0 )
    {
        A = - A - p;
        sens = 1;
    }
    printf("%d %d %d %d", (xmax - xmin - 1), (ymax - ymin - 1), sens, A);
    return 0;
}
