#include <cstdio>
#include <vector>
#define MaxN 1003

using namespace std;

FILE *fin=freopen("aprindere.in","r",stdin);
FILE *fout=freopen("aprindere.out","w",stdout);

int n, m;
vector < vector<int> > v(MaxN);
vector <int> T(MaxN);
vector <int> st(MaxN);

void Read()
{
    scanf("%d %d", &n, &m);
    int c, x;

    for(int i = 0 ; i < n ; ++i)
        scanf("%d ", &st[i]);

    for(int i = 1 ; i <= m ; ++i )
    {
        scanf("%d ", &c);
        scanf("%d %d", &T[c], &x);

        v[c].reserve(x + 1);
        v[c][0] = x;

        for(int j = 1 ; j <= v[c][0] ; ++j )
            scanf("%d", &v[c][j]);
    }

}

void Solve()
{
    int i, j, rez = 0;

    for(i = 0 ; i < n ; ++i)
        if( !st[i] )
        {
            rez += T[i];
            for(j = 1 ; j <= v[i][0] ; ++j )
                st[v[i][j]] = 1 - st[v[i][j]];
        }

    printf("%d", rez);
}

int main()
{
    Read();
    Solve();
}
