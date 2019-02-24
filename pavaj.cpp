#include <fstream>
using namespace std;
ifstream in("pavaj.in");
ofstream out("pavaj.out");
short int L , N , D[701], A[701][301];

void Read()
{
    in >> L >> N;
    for(int i = 1 ; i <= N ; ++i )
        in >> D[i];
}

void Plus(int a, int b)
{
    int i , t = 0;
    for( i = 1 ; i <= A[a][0] || i <= A[b][0] || t ; t /= 10 , ++i )
        A[a][i] = ( t += A[a][i] + A[b][i] ) % 10;
    A[a][0] = i - 1;
}

void Solve()
{
    A[0][0] = A[0][1] = 1;
    for(int i = 1 ; i <= L ; ++i )
    {
        for(int j = 1 ; j <= N ; ++j )
            if( D[j] <= i )
                Plus( i , i - D[j] );
    }
    for(int i = A[L][0] ; i > 0 ; --i )
        out << A[L][i];
}

int main()
{
    Read();
    Solve();
    return 0;
}
