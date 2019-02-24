#include <fstream>
using namespace std;
ifstream in("cmmdc.in");
ofstream out("cmmdc.out");

int main()
{
    long long int a, b, r;
    in >> a >> b;
    while( b )
        r = a % b, a = b, b = r;
    out << a;
    return 0;
}
