#include <fstream>

using namespace std;

ifstream in("basket.in");
ofstream out("basket.out");

long long T, Mod, A[301][301];


void Precalculate_Values()
{
    A[1][0] = 1;

    for(int i = 2 ; i <= 300 ; ++i )
    {
        A[i][0] = 1;
        for(int j = 1 ; j < i ; ++j )
            A[i][j] = ( (j + 1) * A[i - 1][j] + (i - j) * A[i - 1][j - 1] ) % Mod;
    }
}

int main()
{
    in >> T >> Mod;

    Precalculate_Values();

    int a, b;
    for(int i = 1 ; i <= T ; ++i )
    {
        in >> a >> b;
        out << A[a][b] << "\n";
    }

    return 0;
}
