// How about a coding trick?
#include <fstream>
#define DIM 300
using namespace std;
ifstream in("nrbanda.in");
ofstream out("nrbanda.out");


int n, v[DIM], aux[DIM];

void Read()
{
    int i;
    in >> n;
    for(i = 1; i <= n; ++i)
        in >> v[i];
}

void Solve()
{
    int i, j, rot, ind, k;

    for(i = 1; i <= n; ++i)
        if( v[i] != i )
        {
            for(j = i + 1; j <= n && v[j] != i; ++j);
            rot = n - j;
            for(j = n ; j > 0; --j)
            {
                ind = j - rot;
                if(ind < 1)
                    ind += n;
                aux[j] = v[ind];
            }
            //for(j = 1; j <= n; ++j)
               // out << aux[j] << " ";
            for(j = 1; j <= rot; ++j)
                out << 0 << "\n";

            if( i == 1 )
                rot = 0;
            else
            {
                for(j = 1; j < n && aux[j] != i - 1; ++j);
                rot = j;
            }
            for(j = 1; j <= rot; ++j)
                out << n - 1 << "\n";
            for(j = 1; j < n; ++j)
            {
                ind = j + rot;
                if( ind >= n )
                    ind -= (n - 1);
                v[j] = aux[ind];
            }
            v[n] = aux[n];
            //for(j = 1; j <= n; ++j)
                //out << v[j] << " ";

            rot = i;
            for(j = 1; j <= n; ++j)
            {
                ind = j - rot;
                if( ind < 1 )
                    ind += n;
                aux[j] = v[ind];
            }
            for(j = 1; j <= rot; ++j)
                out << 0 << "\n";
            for(j = 1; j <= n; ++j)
            {
                v[j] = aux[j];
                //out << v[j] << " ";
            }
            //out << "\n";
        }
}

int main()
{
    Read();
    Solve();
    return 0;
}
