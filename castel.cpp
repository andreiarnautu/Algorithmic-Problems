// @Worg

#include <cstdio>
#include <queue>
#include <vector>
#define DIM 153
using namespace std;
FILE *fin=freopen("castel.in","r",stdin);
FILE *fout=freopen("castel.out","w",stdout);

const int dx[] = {-1, 1, 0, 0};
const int dy[] = { 0, 0,-1, 1};
queue <int> Q;
vector <int> List[DIM * DIM];
vector <int>::iterator it;
vector <bool> K(DIM * DIM);
bool Viz[DIM][DIM];
int A[DIM][DIM];
int m, n, k;

void Read()
{
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
        {
            scanf("%d", &A[i][j]);
            --A[i][j];
        }
}

void Solve()
{
    int ansCount = 0, i, j, l, I, J;

    Q.push(--k);
    Viz[k / m][k % m] = 1;

    while( !Q.empty() )
    {
        ++ansCount;
        k = Q.front(); Q.pop();
        K[k] = 1;

        for(it = List[k].begin(); it != List[k].end(); ++it)
            if( Viz[*it / m][*it % m] == 0 )
            {
                Viz[*it / m][*it % m] = 1;
                Q.push(*it);
            }
        i = k / m, j = k % m;

        for(l = 0; l < 4; ++l)
        {
            I = i + dx[l], J = j + dy[l];
            if( I < 0 || J < 0 || I >= n || J >= m || Viz[I][J] )
                continue;

            if( K[A[I][J]] )
            {
                Q.push(I * m + J);
                Viz[I][J] = 1;
            }
            else
                List[A[I][J]].push_back(I * m + J);
        }

    }

    printf("%d", ansCount);
}

int main()
{
    Read();
    Solve();
    return 0;
}
