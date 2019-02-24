#include <fstream>
#include <vector>

using namespace std;

ifstream in("maxd.in");
ofstream out("maxd.out");

vector <bool> viz(45000);
int a, b, Primes[10000], k, maxdiv, Min , cnt;


void Ciur()
{
    int i, j;
    Primes[++k] = 2;
    for( i = 3 ; i * i * i * i <= b ; i += 2 )
        if( !viz[i] )
            for( j = i * i ; j * j <= b ; j += (i << 1) )
                viz[j] = 1;

    for( i = 3 ; i * i <= b ; i += 2 )
        if( !viz[i] )
            Primes[++k] = i;
}

int Div(int x)
{
    int p = 1, nr;
    for(int i = 1 ; i <= k && x > 1 && Primes[i] <= x ; ++i )
    {
        nr = 1;
        while( x % Primes[i] == 0 )
        {
            ++nr;
            x /= Primes[i];
        }
        p *= nr;
    }

    if( x > 1 )
        p *= 2;

    return p;

}

int main()
{
    in >> a >> b;
    Ciur();

    int x;
    for(int i = a ; i <= b ; ++i )
    {
        x = Div(i);
        //out << x << " ";
        if( x > maxdiv )
        {
            Min = i;
            maxdiv = x;
            cnt = 1;
        }
        else if( x == maxdiv )
            ++cnt;
    }

    out << Min << " " << maxdiv << " " << cnt;

    return 0;
}
