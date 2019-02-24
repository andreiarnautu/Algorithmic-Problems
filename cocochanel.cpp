#include <fstream>

using namespace std;

ifstream in("cocochanel.in");
ofstream out("cocochanel.out");

int N, M;
int F[33], Max[33], V[100003];



void Add_Number()
{
    int x, i = 1, p = 0;
    in >> x;
    if( x == 1 )
    {
        F[0] = Max[0] = 1;
        return;
    }
    while(i < x)
    {
        i *= 2;
        ++p;
    }
    --p;
    ++F[p];
    if( x > Max[p] )
        Max[p] = x;
}

void Solve(int k)
{
    int st = 0 , dr = 31 , m;
    while( st + 1 < dr )
    {
        m = (st + dr) / 2;
        if( (1 << m) < k )
            st = m;
        else
            dr = m;
    }
    if( (1 << (st + 1)) < k )
        st++;
    //out << st << " ";

    int cnt = 0 , p1 = st - 1;
    if( p1 < 0 )
        p1 = 0;

    while( p1 <= 31 )
    {
       // out << k << " " << p1 << " ";
        if( k <= (1 << p1) && F[p1] > 1 )
        {
            k *= 2;
            ++cnt;
        }
        if( k <= Max[p1] )
        {
            ++cnt;
            k *= 2;
        }
        ++p1;
    }

    out << cnt <<"\n";

}

int main()
{
    in >> N >> M;
    for(int i = 1 ; i <= N ; ++i )
        in >> V[i];

    for(int i = 1 ; i <= M ; ++i )
        Add_Number();

   // for(int i = 1 ; i <= 7 ; ++i )
     //   out << F[i] << " " << Max[i] << "\n";
   // out<< Max[6];
    for(int i = 1 ; i <= N ; ++i )
        Solve( V[i] );
}
