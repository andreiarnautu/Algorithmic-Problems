#include <fstream>

using namespace std;

ifstream in("inter.in");
ofstream out("inter.out");

int N , M, Pos[1001] , V[1001];



int main()
{
    in >> N >> M;

    for(int i = 1 ; i <= N ; ++i )
        Pos[i] = i;

    int x, y;
    for(int i = 1 ; i <= M ; ++i )
    {
        in >> x >> y;
        if( x > y )
        {
            --Pos[x];
            ++Pos[y];
        }
        else
        {
            ++Pos[x];
            --Pos[y];
        }
    }

    for(int i = 1 ; i <= N ; ++i )
        V[Pos[i]] = i;

    for(int i = 1 ; i <= N ; ++i )
        out << V[i] << " ";

    return 0;
}
