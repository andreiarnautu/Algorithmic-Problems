#include <fstream>
using namespace std;

ifstream in("patrate2.in");
ofstream out("patrate2.out");

int v[11000];


int main()
{
    int n, i, t, j;
    v[0] = v[1] = 1;

    in >> n;

    for(j = 1 ; j <= n * n ; ++j)
    {
        for(i = 1, t = 0; i <= v[0] || t ; ++i, t /= 10 )
            v[i] = (t += v[i] * 2) % 10;
        v[0] = i - 1;
    }

    v[0] = i - 1;

    for(j = 2 ; j <= n ; ++j)
    {
        for(i = 1, t = 0; i <= v[0] || t ; ++i , t /= 10 )
            v[i] = (t += v[i] * j) % 10;
        v[0] = i - 1;
    }

    for(i = v[0]; i > 0 ; --i)
        out << v[i];

    return 0;

}
