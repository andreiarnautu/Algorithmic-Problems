#include <fstream>
#include <algorithm>
#include <iomanip>
#define Nmax 101
using namespace std;
ifstream in("invest.in");
ofstream out("invest.out");

int N;
long double A[Nmax], A2[Nmax], B[Nmax], B2[Nmax], V[Nmax];

void Read()
{
    in >> N;
   // scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
      //  scanf("%Lf", & A[i]);
        in >> A[i];
    for(int i = 1 ; i <= N ; ++i )
     //   scanf("%Lf", & A2[i]);
        in >> A2[i];
    for(int i = 1 ; i <= N ; ++i )
      //  scanf("%Lf", & B[i]);
        in >> B[i];
    for(int i = 1 ; i <= N ; ++i )
      //  scanf("%Lf", & B2[i]);
        in >> B2[i];
}

long double Max(long double a, long double b, long double c)
{
    if( a >= b && a >= c )
        return a;
    if( b >= c && b >= a )
        return b;
    return c;
}

long double Maxx(long double a, long double b)
{
    if( a >= b )
        return a;
    return b;
}

void Solve()
{
    V[0] = 100;
    //scanf("%d", &N);
  /*  for(int i = 1 ; i <= N ; ++i )
        printf("%lf ",  A[i]);
    for(int i = 1 ; i <= N ; ++i )
        printf("%lf ",  A2[i]);
    for(int i = 1 ; i <= N ; ++i )
        printf("%lf ",  B[i]);
    for(int i = 1 ; i <= N ; ++i )
        printf("%lf ",  B2[i]);*/
    for(int i = 1 ; i <= N + 1 ; ++i )
        if( i >= 6 )
            V[i] = Max( V[i - 1] , (long double)  ( (long double)V[i - 1] - A[i - 1]) * A2[i - 1], (long double) ( (long double)V[i - 6] - B[i - 6]) * B2[i - 6] );
        else
            V[i] = Maxx( V[i - 1] , (long double) ((long double)V[i - 1] - A[i - 1]) * A2[i - 1] );
  //  set.precision(4);
    //out << fixed();
    setprecision(5);
    out << fixed;
    out <<  V[N + 1];
}

int main()
{
    Read();
    Solve();
    return 0;
}
