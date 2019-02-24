#include <fstream>
#define MOD 1999999973
using namespace std;
ifstream in("lgput.in");
ofstream out("lgput.out");

unsigned long long int N, P, AUX = 1;


int main()
{
    in >> N >> P;
    AUX = N, N = 1;
    for(int i = 1; i <= P ; i <<= 1)
    {
        if( i & P )
            N = 1LL * (N * AUX) % MOD;
        AUX = 1LL * (AUX * AUX) % MOD;
    }
    out << N;
}
