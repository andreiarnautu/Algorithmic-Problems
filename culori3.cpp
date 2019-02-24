// Andi Arnautu
#include <fstream>
#include <cstring>
#define Dim 10000
using namespace std;

ifstream in("culori3.in");
ofstream out("culori3.out");

struct{ int Last[Dim] , Current[Dim];} A[4];
int Sum[10000];
int N;


void Plus(int x, int y)
{
    int i, t = 0;
    for( i = 1 ; i <= A[x].Current[0] || i <= A[y].Last[0] || t ; i++ , t /= 10 )
        A[x].Current[i] = ( t += A[x].Current[i] + A[y].Last[i] ) % 10;
    A[x].Current[0] = i - 1;
}

void Plusx(int x, int y)
{
    int i, t = 0;
    for( i = 1 ; i <= A[x].Current[0] || i <= A[y].Last[0] || t ; i++ , t /= 10 )
        A[x].Current[i] = ( t += A[x].Current[i] + 2 * A[y].Last[i] ) % 10;
    A[x].Current[0] = i - 1;
}

int main()
{
    in >> N;
    A[0].Last[0] = A[1].Last[0] = A[2].Last[0] = A[3].Last[0] = A[4].Last[0] = A[0].Last[1] = A[1].Last[1] = A[2].Last[1] = A[3].Last[1] = A[4].Last[1] = 1;

    for(int i = 2 ; i <= N ; ++i )
    {

        Plus( 0 , 1 );
        Plus( 1 , 0 );
        Plus( 1 , 2 );
        Plusx( 2 , 1 );
        for(int j = 0 ; j < 3 ; ++j )
            for(int l = A[j].Current[0] ; l >= 0 ; --l )
                A[j].Last[l] = A[j].Current[l];
        for(int j = 0 ; j < 3 ; ++j )
            for(int l = 0 ; l <= A[j].Last[0] ; ++l )
                A[j].Current[l] = 0;
    }

    int i, t = 0;
    for( i = 1 ; i <= A[0].Last[0] || i <= A[1].Last[0] || i <= A[2].Last[0] || i <= A[1].Last[0] || i <= A[0].Last[0] || t ; ++i , t /= 10 )
        Sum[i] = ( t += A[0].Last[i] + A[1].Last[i] + A[2].Last[i] + A[1].Last[i] + A[0].Last[i] ) % 10;

    Sum[0] = i - 1;
    for( i = Sum[0] ; i > 0 ; --i )
        out << Sum[i];

    return 0;
}
