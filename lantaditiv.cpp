#include <fstream>

using namespace std;

ifstream in("lantaditiv.in");
ofstream out("lantaditiv.out");

long long int V[152], K, last;

int main()
{
    in >> V[1];
    K = 1;
    last = V[1];

    if( last == 1 )
    {
        out << "3" << "\n" << "1 1 2";
        return 0;
    }

    while( last > 1 )
    {
        if( last % 2 == 0 )
        {
            V[K + 1] = last / 2;
            ++K;
            last = V[K];
        }

        else
        {
            V[K + 1] = last / 2 + 1;
            V[K + 2] = last / 2;
            K += 2;
            last = V[K];
        }

    }

    out << K << "\n";
    for(int i = K ; i > 0 ; --i )
        out << V[i] << " ";

    return 0;

}
