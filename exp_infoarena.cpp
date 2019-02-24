#include <cstdio>
#include <cstring>

using namespace std;

FILE *fin=freopen("exp.in","r",stdin);
FILE *fout=freopen("exp.out","w",stdout);

bool viz[30003];
int Primes[7000], m , n , V[80013], k, F[7000];


void Read()
{
    scanf("%d%d", &m, &n);
    int j, aux, i, p;
    char c[10];

    for( i = 1; i <= n ; ++i )
    {
        scanf("%s", &c);
        aux = 0;
        p = 1;
        for( j = strlen(c) - 1 ; j >= 0 ; --j )
        {
            aux += (c[j] - 48) * p;
            p *= 10;
        }
        V[i] = aux;
       // printf("%d ", V[i]);
    }

}

void Ciur()
{
    int i, j;
    Primes[++k] = 2;
    for( i = 3 ; i * i <= 30000 ; i += 2 )
        if( !viz[i] )
            for( j = i * i ; j <= 30000 ; j += i << 1 )
                viz[j] = 1;
    for(int i = 3; i <= 30000 ; i += 2 )
        if( !viz[i] )
            Primes[++k] = i;
}

void Solve_the_Problem()
{
    int i, j;
    for( i = 1 ; i <= n ; ++i )
    {
        for(int j = 1 ; j <= k && V[i] > 1 ; ++j )
            while( V[i] % Primes[j] == 0 )
            {
                ++F[j];
                V[i] /= Primes[j];
            }
    }

    bool ok = 1;
    for(int i = 1 ; i <= k ; ++i )
    {
        if( F[i] % m != 0 )
        {
            ok = 0;
            break;
        }
    }

    if( !ok )
        printf("0");

    else
    {
        printf("1\n");
        for(int i = 1 ; i <= k ; ++i )
            if( F[i] )
                printf("%d %d\n", Primes[i] , F[i] / m );
    }

}

int main()
{
    Read();
    Ciur();
    Solve_the_Problem();
    return 0;
}
