#include <fstream>
#define Dim 100003

using namespace std;

ifstream in("aranjare2.in");
ofstream out("aranjare2.out");

int N, V[2 * Dim], Pos[2 * Dim];


int main()
{
    in >> N;
    for(int i = 1 ; i <= 2 * N ; ++i )
        V[i] = Pos[i] = i;
    for(int i = 1 ; i < N ; ++i )
    {
        if( V[i * 2] != N + i )
        {
            V[Pos[N + i]] = V[2 * i];
            Pos[V[2 * i]] = Pos[N + i];
            out << 2 * i << " " <<  Pos[N + i] << "\n";
        }
        if( V[2 * i + 1] != i + 1 )
        {
            V[Pos[i + 1]] = V[2 * i + 1];
            Pos[V[2 * i + 1]] = Pos[i + 1];
            out << 2 * i + 1 << " " << Pos[i + 1] << "\n";
        }
    }
    return 0;


}
