#include <fstream>
#include <vector>

using namespace std;

ifstream in("difprim.in");
ofstream out("difprim.out");

int a, b, Diff, first, second, nr, n1, n2;
vector <bool> c(10000003);


void Find_the_Primes()
{
    int i, j;

    if( a % 2 == 0 )
        for(i = a ; i <= b ; i += 2 )
            c[i] = 1;
    else
        for(i = a + 1 ; i <= b ; i += 2 )
            c[i] = 1;

    c[2] = 0;

    for(i = 3 ; i * i <= b ; i += 2 )
        if( !c[i] )
            for(j = i * i ; j <= b ; j += 2 * i )
                c[j] = 1;
}

void Search()
{
    int i;

    for( i = a ; i <= b ; ++i )
        if( !c[i] )
        {
            if( !nr )
            {
                ++nr;
                first = i;
            }

            else if( nr == 1 )
            {
                ++nr;
                second = i;
                Diff = second - first;
                n1 = first;
                n2 = second;
            }

            else
            {
                first = second;
                second = i;
                if( second - first > Diff )
                {
                    Diff = second - first;
                    n1 = first;
                    n2 = second;
                }
            }
        }

    if( nr < 2 )
        out << "-1";
    else
        out << n1 << " " << n2;
}

int main()
{
    in >> a >> b;
    Find_the_Primes();
    Search();
}
