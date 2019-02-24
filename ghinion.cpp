#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin=freopen("ghinion.in","r",stdin);
FILE *fout=freopen("ghinion.out","w",stdout);

int n, k;
int comb[25][25], F[12], S[300], Aux[450], Sol[450], Adev[450];

void Gen_Comb()
{
    int i, j;
    comb[1][1] = 1;
    for(i = 0; i <= 21; ++i)
        comb[i][0] = 1;

    for(i = 2; i <= 21; ++i)
        for(j = 1; j <= i; ++j)
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
}

void Sum_Combination()
{
    int i, j, t, ramase = n, val;
    Aux[0] = Aux[1] = 1;

    //printf("");

    for(j = 0; j <= k; ++j)
    {
        val = comb[ramase][F[j]];
       // printf("%d ", val);

        for(i = 1, t = 0; i <= Aux[0] || t; i++, t /= 10)
            Aux[i] = (t += Aux[i] * val) % 10;
        Aux[0] = i - 1;

        ramase -= F[j];
    }

    /*for(i = Aux[0]; i > 0; --i)
        printf("%d", Aux[i]);
    printf("\n");*/

    for(i = 1, t = 0; i <= Sol[0] || i <= Aux[0] || t; t /= 10, ++i)
        Sol[i] = (t += Sol[i] + Aux[i] ) % 10;
    Sol[0] = i - 1;

    for(i = 1; i <= Aux[0]; ++i)
        Aux[i] = 0;
    Aux[0] = 0;

}

void Verif()
{
    int i, j, l, sumtotal = 0, summax = 0;
    for(i = 0; i <= k; ++i)
    {
        sumtotal += i * F[i];
    }

    if( sumtotal % 2 == 1 )
        return;

    S[0] = 1;

    for(l = 0; l <= k; ++l)
        for(i = 1; i <= F[l]; ++i)
        {
            for(j = summax; j >= 0; --j)
                if( S[j] && l + j <= sumtotal / 2 )
                {
                    S[l + j] = 1;
                    if( l + j == sumtotal / 2 )
                    {
                        for(l = 0; l <= sumtotal / 2; ++l)
                            S[l] = 0;
                        Sum_Combination();
                        return;
                    }
                }
            summax = min( sumtotal / 2, summax + l );
        }
    for(i = 0; i <= sumtotal / 2; ++i)
        S[i] = 0;
}

void Gen(int x, int nr)
{
    if( x > k )
        Verif();
    else
    {
        if( x == k )
        {
            F[k] = nr;
            Gen(x + 1, 0);
            return;
        }
        for(int i = 0; i <= nr; ++i)
        {
            F[x] = i;
            Gen(x + 1, nr - i);
        }
    }
}

void Write()
{
    int i, t, j;
    Adev[0] = Adev[1] = 1;
    for(j = 1; j <= n; ++j)
    {
        for(i = 1, t = 0; i <= Adev[0] || t; t /= 10, ++i)
            Adev[i] = (t += Adev[i] * (k + 1) ) % 10;
        Adev[0] = i - 1;
    }

    //for( i = Sol[0]; i > 0; --i)
        //printf("%d", Sol[i]);

    for( t = 0, i = 1; i <= Adev[0]; ++i )
    {
        Adev[i] -= ((i <= Sol[0]) ? Sol[i] : 0) + t;
        Adev[i] += (t = Adev[i] < 0) * 10;
    }

    while( Adev[Adev[0]] == 0  && Adev[0] > 1 )
        Adev[0]--;

    for( i = Adev[0]; i > 0; --i)
        printf("%d", Adev[i]);
}


int main()
{
    Gen_Comb();
    scanf("%d %d ", &n, &k);
    Sol[0] = 1, Sol[1] = 0;
    Gen(0, n);
    Write();
    return 0;
}
