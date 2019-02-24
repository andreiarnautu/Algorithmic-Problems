#include <fstream>
#include <string>
#include <queue>
#define DIM 1010
using namespace std;
ifstream in("drum6.in");
ofstream out("drum6.out");


string s[DIM], sol;
bool OK[DIM][DIM];
int n, m;

void Read()
{
    int i, j;

    in >> n >> m;
    for( i = 1; i <= n; ++i )
        in >> s[i];

    sol = s[1][0]; OK[1][1] = true;

    for(i = 1; i <= n; ++i)
        for(j = 1; j <= m; ++j)
        {
            if( i == 1 && j == 1 )
                ++j;

            if( i > 1 && OK[i - 1][j] == true && s[i - 1][j - 1] == sol[i + j - 3] )
                OK[i][j] = true;
            if( j > 1 && OK[i][j - 1] == true && s[i][j - 2] == sol[i + j - 3] )
                OK[i][j] = true;

            if( OK[i][j] )
            {
                if( i + j - 2 >= sol.length() )
                    sol += s[i][j - 1];
                else
                {
                    if( sol[i + j - 2] > s[i][j - 1] )
                    {
                        sol.erase(sol.begin() + i + j - 2, sol.end());
                        sol += s[i][j - 1];
                    }
                }
            }
        }

    out << sol;
}

int main()
{
    Read();
    return 0;
}
