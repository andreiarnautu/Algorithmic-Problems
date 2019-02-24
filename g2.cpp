#include <fstream>
using namespace std;
ifstream in("g2.in");
ofstream out("g2.out");

int F[10], v[] = {2, 3, 5, 7};

int main()
{
    int i, n;
    in >> n;
    if( n == 1 )
    {
        out << 1;
        return 0;
    }
    for(i = 0; i < 4; ++i)
        while( n % v[i] == 0 )
        {
            n /= v[i], ++F[v[i]];
        }
    if( n > 1 )
    {
        out << 0;
        return 0;
    }
    F[8] = F[2] / 3;
    F[2] %= 3;
    F[9] = F[3] / 2;
    F[3] %= 2;
    if( F[2] && F[3] )
    {
        --F[2], --F[3], ++F[6];
    }
    if( F[2] == 2 )
    {
        F[2] -= 2, ++F[4];
    }
    for(i = 1; i < 10; ++i)
        while( F[i] )
        {
            out << i;
            --F[i];
        }
}
