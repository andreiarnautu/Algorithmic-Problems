#include <cstdio>
#include <algorithm>
#define Inf 10000000

using namespace std;

FILE *fin=freopen("cerc5.in","r",stdin);
FILE *fout=freopen("cerc5.out","w",stdout);

int N , K , V[100013], Best[100013], Min[100004], Max = 1, Primes[100002];
bool Viz[1000000];


void Solve1()
{
    scanf("%d%d", &N, &K);

    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%d", &V[i]);
        Min[i] = Inf;
    }

    Best[1] = 1;
    Min[1] = V[1];

    int last, biggest = 1;
    for(int i = 2 ; i <= N ; ++i )
    {
        last = 0;
        for(int j = biggest ; j > 0 ; --j )
            if( Min[j] < V[i] )
            {
                last = j;
                break;
            }
        if( last == biggest )
        {
            ++biggest;
            Best[biggest] = 1;
            Min[biggest] = V[i];
        }
        else
            if( Min[last + 1] > V[i] )
                Min[last + 1] = V[i];
    }

    printf("%d", biggest);
}

void Generate(int x)
{
    int i , j;
    for( i = 3 ; i * i <= 1000000 ; i += 2 )
        if( !Viz[i] )
            for( j = i * i ; j <= 1000000 ; j += 2 * i )
                Viz[j] = 1;

    Primes[1] = 2;
    int it = 1;
    for(int i = 3 ; i <= 1000000 && it <= x ; i += 2 )
        if( !Viz[i] )
            Primes[++it] = i;
}


void Solve2()
{
    scanf("%d%d", &N, &K);

    for(int i = 1 ; i <= N ; ++i )
        scanf("%d", &V[i]);

    Generate(K + 1);

    int pos, pos1, pos2, nr, r , c;

    pos = 1;

    for(int i = 1 ; i <= K ; ++i )
    {
        nr = Primes[i];

        if( pos == 1 )
        {
            pos += nr;
            pos %= N;
            if( pos == 0 )
                pos = N;
        }

        else
        {
            r = nr % (N - 1);
            c = nr / (N - 1);

            if( pos - 1 <= r )
                --pos;

            pos -= c;

            while( pos < 1 )
                pos += N;

            //if( pos == 0 )
              //  pos = N;
        }

        pos %= N;
        if( pos == 0 )
            pos = N;


    }
   // printf("%d ",pos);

    pos1 = pos + 1;
    pos2 = pos - 1;

    if( pos1 > N )
        pos1 -= N;

    if( pos2 < 1 )
        pos2 += N;

    //printf("%d ",pos1);

    int aux1, aux2;

    for(int i = K ; i > 0 ; --i )
    {
        nr = (Primes[i] + 1) % N;

        if( nr == 0 )
            nr = N;

        if( pos1 == nr )
        {
            pos1 = 1;
            continue;
        }

        aux1 = nr;
       // if( aux1 == 0 )
         //   aux1 = N;

        r = Primes[i] % (N - 1);
        c = Primes[i] / (N - 1);

        aux2 = aux1 - r;
        while( aux2 < 1 )
            aux2 += N;

        if( aux2 <= aux1 )
        {
            if( aux2 <= pos1 && pos1 < aux1 )
                ++pos1;
        }

        else
        {
            if( pos1 < aux1 || pos1 >= aux2 )
                ++pos1;
        }

        pos1 += c;

        pos1 %= N;
        if( pos1 == 0 )
            pos1 = N;

        //printf("%d %d %d\n", aux1 , aux2 , pos1);

        //printf("%d %d %d\n", aux1, aux2, pos1);
        //printf("%d ",pos1);
    }

    for(int i = K ; i > 0 ; --i )
    {
        nr = (Primes[i] + 1) % N;

        if( nr == 0 )
            nr = N;

        if( pos2 == nr )
        {
            pos2 = 1;
            continue;
        }

        aux1 = nr;
       // if( aux1 == 0 )
         //   aux1 = N;

        r = Primes[i] % (N - 1);
        c = Primes[i] / (N - 1);

        aux2 = aux1 - r;
        while( aux2 < 1 )
            aux2 += N;

        if( aux2 <= aux1 )
        {
            if( aux2 <= pos2 && pos2 < aux1 )
                ++pos2;
        }

        else
        {
            if( pos2 < aux1 || pos2 >= aux2 )
                ++pos2;
        }

        pos2 += c;

        pos2 %= N;
        if( pos2 == 0 )
            pos2 = N;

        //printf("%d %d %d\n", aux1, aux2, pos1);
        //printf("%d ",pos1);
    }

    pos1 %= N;
    pos2 %= N;

    if( pos1 == 0 )
        pos1 = N;

    if( pos2 == 0 )
        pos2 = N;

    printf("%d %d",V[pos1], V[pos2]);
}

int main()
{
    int p;
    scanf("%d", &p);
    if( p == 1 )
        Solve1();

    else
        Solve2();

    return 0;
}
