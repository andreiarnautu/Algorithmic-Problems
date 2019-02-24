#include <vector>
#include <cstdio>
#include <string>
#include <cstdlib>
using namespace std;
FILE *fin=freopen("coduri.in","r",stdin);
FILE *fout=freopen("coduri.out","w",stdout);

vector <bool> viz(1000001);
int Primes[1000000], no, F1[20][1000000], k, nn;
char s[30];
string sir, s2, s3, s4;

void Gen()
{
    int i;
    long long int j;
    Primes[++no] = 2;
    for(i = 3; i <= 1000000 && no <= 2300; i += 2)
        if( !viz[i] )
        {
            Primes[++no] = i;
            for(j = 1LL * i * i; j <= 100000; j += 2LL * i)
                viz[j] = 1;
        }
}

void Solve(int q)
{
    int pos, pos1, pos2;
    long long int nr1, nr2 = 1, nr3, nr4, c1, c2, val1, val2, numitor = 0;
    gets(s);
    sir = s;

    pos = sir.find(',');
    if( pos == -1 )
        pos = sir.length();

    s2 = sir.substr(0, pos);
    nr1 = atoi(s2.c_str());

    if( pos != sir.length() )
    {
        nr3 = 0;
        pos1 = sir.find('(');
        if( pos1 == -1 )
            pos1 = sir.length();
            s3 = sir.substr(pos + 1, pos1);

        nr3 = atoi(s3.c_str());
        nr4 = 0;
        if( pos1 != sir.length() )
        {
            s4 = sir.substr(pos1 + 1, sir.length() - 2);
            nr4 = atoi(s4.c_str());
        }

        if( nr4 )
        {
            c1 = pos1 - pos - 1;
            c2 = sir.length() - 2 - pos1;
            int aux;
            aux = nr3;
            for(int i = 1; i <= c2; ++i)
                nr3 *= 10, numitor = numitor * 10 + 9;
            for(int i = 1; i <= c1; ++i)
                numitor *= 10;
            nr3 += nr4;
            nr3 -= aux;
        }
        else
        {
            c1 = sir.length() - 1 - pos;
            numitor = 1;
//            nr3 = atoi()
            for(int i = 1; i <= c1; ++i)
                numitor *= 10;
        }
        nr1 = nr3 + 1LL * nr1 * numitor;
    }

    else
    {
        numitor = 1;
    }
    //printf("%d ", Primes[no + 1]);

    //printf("%lld %lld\n", nr1, numitor);

    for(int i = 1; i <= no + k && nr1 > 1; ++i)
    {
        while( nr1 % Primes[i] == 0 )
        {
            ++F1[q][i];
            nr1 /= Primes[i];
        }
    }

    while(nr1 > 1)
    {
        int i;
        for(i = Primes[no + k]; nr1 > 1 && i * i <= nr1 ; i += 2)
            if( nr1 % i == 0 && !viz[i] )
            {
                int j;
                for(j = no + k; j > 0; --j)
                {
                    if( Primes[j] > i )
                    {
                        Primes[j + 1] = Primes[j];
                        for(int l = q; l <= nn; ++l)
                        {
                            F1[l][j + 1] = F1[l][j];
                            F1[l][j] = 0;
                        }
                    }
                    else
                        break;
                }
                Primes[j + 1] = i;
                ++k;
                while( nr1 % i == 0 )
                {
                    nr1 /= i;
                    ++F1[q][j + 1];
                }
            }
        if( nr1 > 1 )
        {
            i = nr1;
            int j;
                for(j = no + k; j > 0; --j)
                {
                    if( Primes[j] > i )
                    {
                        Primes[j + 1] = Primes[j];
                        for(int l = q; l <= nn; ++l)
                        {
                            F1[l][j + 1] = F1[l][j];
                            F1[l][j] = 0;
                        }
                    }
                    else
                        break;
                }
            Primes[j + 1] = i;
                ++k;
                while( nr1 % i == 0 )
                {
                    nr1 /= i;
                    ++F1[q][j + 1];
                }
        }
    }

    for(int i = 1; i <= no + k && numitor > 1; ++i)
    {
        while( numitor % Primes[i] == 0 )
        {
            --F1[q][i];
            numitor /= Primes[i];
        }
    }

    while(numitor > 1)
    {
        int i;
        for(i = Primes[no + k]; numitor > 1 && i * i <= numitor; i += 2)
            if( numitor % i == 0 && !viz[i] )
            {
                int j;
                for(j = no + k; j > 0; --j)
                {
                    if( Primes[j] > i )
                    {
                        Primes[j + 1] = Primes[j];
                        for(int l = q; l <= nn; ++l)
                        {
                            F1[l][j + 1] = F1[l][j];
                            F1[l][j] = 0;
                        }
                    }
                    else
                        break;
                }
                Primes[j + 1] = i;
                ++k;
                while( numitor % i == 0 )
                {
                    numitor /= i;
                    --F1[q][j + 1];
                }
            }
        if( numitor > 1 )
        {
            i = numitor;
            int j;
                for(j = no + k; j > 0; --j)
                {
                    if( Primes[j] > i )
                    {
                        Primes[j + 1] = Primes[j];
                        for(int l = q; l <= nn; ++l)
                        {
                            F1[l][j + 1] = F1[l][j];
                            F1[l][j] = 0;
                        }
                    }
                    else
                        break;
                }
                Primes[j + 1] = i;
                ++k;
                while( numitor % i == 0 )
                {
                    numitor /= i;
                    ++F1[q][j + 1];
                }
        }
    }


   // for(int i = 1; i <= no && nr1 > 1; ++i)

}

int main()
{
    int n;
    Gen();
    for(scanf("%d ", &n), nn = n; n > 0; --n)
    {
        Solve(n);
    }
    for(int i = nn; i > 0; --i)
    {
        printf("%d ", no + k);
        for(int j = no + k; j > 0; --j)
            printf("%d ", F1[i][j]);
        printf("\n");
    }
    return 0;
}
