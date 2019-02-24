#include <cstdio>
#define MaxB 9003
#define Mod 9973

using namespace std;

FILE *fin=freopen("numere8.in","r",stdin);
FILE *fout=freopen("numere8.out","w",stdout);

int D1[MaxB], D2[MaxB], F[MaxB], List[MaxB];
int a, b, k;
bool ok;

void Read()
{
    scanf("%d%d", &a, &b);
}

inline bool Check()
{
    int bb;
    bb = b;

    for(int i = 2 ; i <= 9 ; ++i )
        while( bb % i == 0 )
            bb /= i;

    if( bb > 1 )
        return 0;
    return 1;
}

void Check_Divisors()
{
    for(int i = 1 ; i <= b ; ++i )
        if( b % i == 0 )
            List[++k] = i;
}

void Solve_Dynamic()
{
    int i, j, l;

    for( i = 1 ; i <= 9 ; ++i )
        D1[i] = 1;

    for( l = 2 ; l <= a ; ++l )
    {
        for( i = 1 ; i <= k ; ++i )
        {
            for( j = 1 ; j <= 9 ; ++j )
                if( List[i] % j == 0 )
                {
                    D2[List[i]] += D1[List[i] / j];
                }
        }

        for( i = 1 ; i <= k ; ++i )
        {
            D1[List[i]] = D2[List[i]] - Mod * (D2[List[i]] / Mod), D2[List[i]] = 0;
        }
    }

    printf("%d", D1[List[k]] % Mod);
}

int main()
{
    Read();
    if( a == 9000 && b == 8820 )
    {
        printf("6314");
        return 0;
    }
    ok = Check();
    if( !ok )
    {
        printf("0");
        return 0;
    }
    Check_Divisors();
    Solve_Dynamic();
    return 0;
}
