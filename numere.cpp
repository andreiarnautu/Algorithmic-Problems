#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin=freopen("numere.in","r",stdin);
FILE *fout=freopen("numere.out","w",stdout);

inline int Win(int x, int y)
{
    if( y == 0 )
        return 0;
    if( x < 2 * y )
        return 1 - Win(y, x - y);
    return 1;
}

void Solve()
{
    int x, y;
    scanf("%d %d", &x, &y);
    if( x < y )
        swap(x, y);

    printf("%d\n", 2 - Win(x, y));
}

int main()
{
    int teste;
    for(scanf("%d", &teste); teste > 0; --teste)
        Solve();
    return 0;
}
