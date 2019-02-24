#include <fstream>
using namespace std;
ifstream in("drepte2.in");
ofstream out("drepte2.out");
int main()
{
    long long int a;
    in>>a;
    out<<1+(a*(a+1))/2;
}
