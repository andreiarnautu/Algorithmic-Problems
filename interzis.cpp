#include <fstream>
#define Mod 101267
#define NMax 15003

using namespace std;

ifstream in("interzis.in");
ofstream out("interzis.out");
long long int N, L, V[NMax];


int main()
{
    in >> N >> L;
    V[0] = 1;
    for(int i = 1 ; i < L ; ++i)
        V[i] = ( V[i - 1] * 2 ) % Mod;
    V[L] = ( V[L - 1] * 2 - 1 ) % Mod;
    for(int i = L + 1 ; i <= N ; ++i )
        V[i] = ( V[i - L] * V[L] ) % Mod;
    out << V[N];

    return 0;

}
