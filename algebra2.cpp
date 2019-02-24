#include <fstream>
using namespace std;
ifstream in("algebra2.in");
ofstream out("algebra2.out");
unsigned long long int N, R, K, X, P = 1, Mod = 1000000009;

void Raise()
{
    while( X > 0 )
    {
        if( X & 1 )
        {
            P = ( P * R ) % Mod;
            --X;
        }
        R = (R * R) % Mod;
        X >>= 1;
    }
}

int main()
{
    in >> N;
    if( N % 2 == 0 )
        X = (( (N / 2) % (Mod - 1) ) * ( (N + 1) % (Mod - 1) )) % (Mod - 1);
    else
        X = (( (N) % (Mod - 1) ) * ( ((N + 1) / 2) % (Mod - 1) )) % (Mod - 1);
    R = N % Mod;
    Raise();
    out << P;
    return 0;
}
