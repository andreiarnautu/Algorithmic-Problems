#include <fstream>
using namespace std;
ifstream in("fractii.in");
ofstream out("fractii.out");
int N;

void Write(int a, int b)
{
    int A, B, r;
    A = a;
    B = b;
    while( b )
    {
        r = a % b;
        a = b;
        b = r;
    }
    A /= a;
    B /= a;
    out << A << " " << B << '\n';
}

int main()
{
    in >> N;
    Write( N , 2 );
    for(int i = N - 1 ; i > 0 ; --i )
        Write( i , N - 1 );
    return 0;
}
