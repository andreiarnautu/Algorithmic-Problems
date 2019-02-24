#include <fstream>
#include <cstring>
using namespace std;
ifstream in("numar3.in");
ofstream out("numar3.out");

int n;
int F[12];
char c;

int main()
{
    int i, j, last, current, pos = 1, nr = 0;

    in >> n >> c;
    ++F[last = c - 48];

    for(i = 2; i <= n ; ++i)
    {
        in >> c;
        current = c - 48;
        if( current <= last )
            ++F[current];
        else
        {
            memset(F, 0, sizeof(F));
            pos = i - 1;
            nr = last;
            ++F[current];
        }
        last = current;
    }

    ifstream in("numar3.in");
    in >> n;

    for(i = 1; i < pos ; ++i)
    {
        in >> c;
        out << c;
    }

    for(i = nr + 1; i <= 9 ; ++i)
        if( F[i] )
        {
            out << i;
            --F[i];
            break;
        }
    ++F[nr];
    for(i = 0; i <= 9 ; ++i)
        for(j = 1; j <= F[i]; ++j)
            out << i;
    return 0;
}
