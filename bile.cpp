// Aplicatie : paduri de submultimi disjuncte cu numarul elementelor din fiecare grup

#include <cstdio>
#include <vector>
#define DIM 260

using namespace std;
FILE *fin=freopen("bile.in","r",stdin);
FILE *fout=freopen("bile.out","w",stdout);

const int dx[] = {-1, 1, 0, 0};
const int dy[] = { 0, 0, 1,-1};

vector < pair<int,int> > V;
vector <int> Q;
vector <int>::iterator it;

int n, Father[DIM * DIM], Members[DIM * DIM];

void Read()
{
    int x, y;
    scanf("%d", &n);
    for(int i = 1; i <= n * n; ++i)
    {
        scanf("%d %d ", &x, &y);
        V.push_back(make_pair(x , y));
    }
}

int Group(int x)
{
    if( x != Father[x] )
        Father[x] = Group(Father[x]);
    return Father[x];
}

void Unite(int x, int y)
{
    int xx, yy;
    xx = Group(x);
    yy = Group(y);
    Father[yy] = xx;
    Members[xx] += Members[yy];
}

void Solve()
{
    int x, y, val, X, Y, val2, best = 0;

    for(int i = n * n - 1; i > 0; --i)
    {
        x = V[i].first, y = V[i].second;
        val = (x - 1) * n + y;
        Father[val] = val, Members[val] = 1;

        for(int j = 0; j < 4; ++j)
        {
            X = x + dx[j], Y = y + dy[j];
            if( X > 0 && X <= n && Y > 0 && Y <= n )
                val2 = (X - 1) * n + Y;
            else
                continue;

            if( Group(val2) != Group(val) && Father[val2] != 0 )
                Unite(val, val2);

        }
        if( Members[val] > best )
            best = Members[val];
        Q.push_back(best);
    }

    for(it = Q.end() - 1; it >= Q.begin(); --it)
        printf("%d\n", *it);
    printf("0");
}

int main()
{
    Read();
    Solve();
    return 0;
}
