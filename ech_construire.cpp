// It's not the load that breaks you down, it's the way you carry it. :)
#include <cstdio>
#include <cstring>
#define DIM 30
using namespace std;
FILE *fin=freopen("ech.in","r",stdin);
FILE *fout=freopen("ech.out","w",stdout);

int A[DIM], S[2], Smax[2];
char s[DIM];

void Read()
{
    scanf("%s", s);
    A[0] = strlen(s);
    for(int i = A[0]; i > 0; --i)
        A[i] = s[ A[0] - i ] - 48;
}

void Build()
{
    int i, paritate, samesum, difsum, add, start, rest;

    for(i = 1; i <= A[0]; ++i)
        S[i % 2] += A[i];

    for(i = 1; i <= A[0] + 1; ++i)
    {
        paritate = i % 2;

        if( i > 1 )
        {
            Smax[1 - paritate] += 9;
            A[i - 1] = 0;
        }

        S[paritate] -= A[i];
        samesum = S[paritate];
        difsum = S[1 - paritate];

        if( A[i] < 9 )
        {

            if( samesum + A[i] < difsum )
            {
                if( samesum + Smax[paritate] + 9 < difsum )
                    continue;

                if( samesum + Smax[paritate] + A[i] + 1 >= difsum )
                    add = 1;

                else
                    add = difsum - ( samesum + A[i] + Smax[paritate] );

                start = 2 - paritate;
                rest = difsum - ( samesum + A[i] + add );
            }

            else
            {
                if( difsum + Smax[1 - paritate] < samesum + A[i] + 1 )
                    continue;

                add = 1;
                start = 1 + paritate;
                rest = samesum + A[i] + 1 - difsum;
            }

            A[i] += add;
            while(start < i)
            {
                if( rest >= 9 )
                    A[start] = 9;
                else
                    A[start] = rest;
                rest -= A[start];
                start += 2;
            }

            break;
        }
    }

    if( A[A[0] + 1] )
        ++A[0];

    for(i = A[0]; i > 0; --i)
        printf("%d", A[i]);
}

int main()
{
    Read();
    Build();
    return 0;
}
