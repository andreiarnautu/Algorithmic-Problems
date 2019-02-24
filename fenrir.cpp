#include <fstream>
using namespace std;
ofstream out("fenrir.out");
ifstream in("fenrir.in");



int main()
{
    int Sum = 0;

    out << "99" << "\n";

    for(int i = 1 ; i <= 9 ; ++i )
        for(int j = 10 ; j <= 20 ; ++j )
            out << i << " " << j << "\n";

    return 0;

}
