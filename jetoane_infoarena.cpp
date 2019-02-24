#include <fstream>
#define Dim 50013

using namespace std;

ifstream in("jetoane.in");
ofstream out("jetoane.out");

int x, N, M, F1[Dim], F2[Dim], Min , Max, n1, n2;


int main()
{
    in >> N >> M;

    for(int i = 1 ; i <= N ; ++i )
    {
        in >> x;
        ++F1[x];
    }

    for(int i = 1 ; i <= M ; ++i )
    {
        in >> x;
        ++F2[x];
    }

    for(int i = 1 ; i <= 50000 ; ++i )
        if( F1[i] && F2[i] )
        {
            Min = i;
            break;
        }

    for(int i = 50000 ; i > 0 ; --i )
        if( F1[i] && F2[i] )
        {
            Max = i;
            break;
        }

    for(int i = Min + 1 ; i < Max ; ++i )
    {
        if( F1[i] )
            ++n1;
        if( F2[i] )
            ++n2;
    }

    if( N - n1 > M - n2 )
        out << Min << " " << Max << " 1";
    else if( N - n1 < M - n2 )
        out << Min << " " << Max << " 2";
    else
        out << Min << " " << Max << " 0";

    return 0;
}
