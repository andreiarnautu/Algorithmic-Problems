#include <fstream>
#include <vector>
#include <string>
#define MaxN 253
#define MaxM 2003
using namespace std;

ifstream in("fold.in");
ofstream out("fold.out");

int A[MaxN][MaxM];
string S;
int n, m, Bits[(1 << 17) + 1];

void Count_Bits()
{
    int i, val = 1 << 17;

    Bits[1] = 1;
    for(i = 2; i <= val ; ++i)
    {
        if( i % 2 == 0 )
            Bits[i] = Bits[i / 2];
        else
            Bits[i] = Bits[i - 1] + 1;
    }
}

void Read()
{
    int i, j, len, pow, pos, ret;
    in >> n >> m;
    getline(in,S);

    for(i = 1; i <= n ; ++i)
    {
        getline(in,S);
        pow = 1, ret = 0, pos = 0;
        for(j = 0, len = S.size(); j < len; j += 2)
        {
            ret += (S[j] - 48) * pow;
            pow *= 2;
            if( pow == 1 << 16 )
            {
                pow = 1;
                A[i][++pos] = ret;
                ret = 0;
            }
        }
        if( ret )
            A[i][++pos] = ret;
    }

}

void Solve()
{
    int i, j, l, cnt, nr, mask,a , b, c;
    long long sol = 0;

    nr = m / 16;
    if(m % 16)
        ++nr;


    for(i = 1; i < n ; ++i)
        for(j = i + 1; j <= n ; ++j)
        {
            cnt = 0;
            for(l = 1; l <= nr ; ++l)
            {
                cnt += Bits[A[i][l] & A[j][l]];
            }
            sol += 1LL * cnt * (cnt - 1) / 2;
        }
    out << sol;
}

int main()
{
    Count_Bits();
    Read();
    Solve();
    return 0;
}
