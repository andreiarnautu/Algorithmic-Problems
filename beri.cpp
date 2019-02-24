#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream in("beri.in");
ofstream out("beri.out");

long long p=1,n,k,q,x,y,z,s=0,i,elem,sum;

vector <long long int> c;

int main()
{
    in >> n >> k >> q >> x >> y >> z;

    c.push_back(q);

    for(i = 2; i <= n ; i++ )
    {
        elem=( c[i-2] * x + y ) % z + k;
        c.push_back(elem);
    }

    nth_element(c.begin(), c.begin() + (n - k) , c.end());

    elem = c[n - k];

    for(vector<long long int>::iterator it = c.begin() ; it != c.end() ; ++it )
        if( *it >= elem )
            sum += *it;

    sum -= k * (k - 1) / 2;

    out << sum;
    return 0;
}
