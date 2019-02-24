#include <fstream>
#define DIM 100003
using namespace std;
ifstream in("disjoint.in");
ofstream out("disjoint.out");

int Father[DIM], Members[DIM];
int n, m;

inline void Read()
{
    in >> n >> m;
    for(int i = 1; i <= n; ++i)
        Father[i] = i, Members[i] = 1;
}

inline int Group(int x)
{
    if( x != Father[x] )
        Father[x] = Group(Father[x]);
    return Father[x];
}

inline void Unite(int x, int y)
{
    x = Group(x);
    y = Group(y);
    Members[y] += Members[x];
    Father[x] = y;
}

inline void Solve()
{
    int op, x, y;
    for(int i = 1; i <= m; ++i)
    {
        in >> op >> x >> y;
        if(op == 1)
            Unite(x, y);
        else
        {
            if( Group(x) == Group(y) )
                out << "DA\n";
            else
                out << "NU\n";
        }
    }

    int best = 50000;
    for(int i = 1; i <= n; ++i)
        if( Members[i] < best )
            best = Members[i];
    printf("%d", best);
}

int main()
{
    Read();
    Solve();
    return 0;
}
