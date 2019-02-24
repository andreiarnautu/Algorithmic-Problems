#include <fstream>
#define MaxK 1003
#define Mod 4001

using namespace std;

ifstream in("div3.in");
ofstream out("div3.out");

int N, K, c;
int F0, F1, F2;
int D[3][MaxK];

int main()
{
    in >> N >> K;
    for(int i = 1 ; i <= N ; ++i )
    {
        in >> c;
        if( c % 3 == 0 )
            ++F0;
        if( c % 3 == 1 )
            ++F1;
        if( c % 3 == 2 )
            ++F2;
    }

    D[0][1] = F0;
    D[1][1] = F1;
    D[2][1] = F2;

    for(int i = 2 ; i <= K ; ++i )
    {
        D[0][i] = ( D[0][i - 1] * F0 + D[1][i - 1] * F2 + D[2][i - 1] * F1 ) % Mod;
        D[1][i] = ( D[0][i - 1] * F1 + D[1][i - 1] * F0 + D[2][i - 1] * F2 ) % Mod;
        D[2][i] = ( D[0][i - 1] * F2 + D[1][i - 1] * F1 + D[2][i - 1] * F0 ) % Mod;
    }

    out << D[0][K];

    return 0;
}
