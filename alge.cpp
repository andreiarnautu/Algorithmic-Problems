#include <cstdio>
#include <queue>
using namespace std;

FILE *fin=freopen("alge.in","r",stdin);
FILE *fout=freopen("alge.out","w",stdout);

const int dx[8] = {0,  0, 0,  0, 1, -1};
const int dy[8] = {0,  0, 1, -1, 0,  0};
const int dz[8] = {1, -1, 0,  0, 0,  0};

queue <int> Cx;
queue <int> Cy;
queue <int> Cz;

int a[36][36][36];
int n, m;

void Read()
{
    int x, y, z;
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++i)
    {
        scanf("%d%d%d", &x, &y, &z);
        a[x][y][z] = -1;
    }
}

void Lee()
{
    int X, Y, Z, i, j, l, s, pos, xx, yy, zz;

    Cx.push(1); Cy.push(1); Cz.push(1);

    a[1][1][1] = 1;

    while( !Cx.empty() && a[n][n][n] == 0 )
    {
        X = Cx.front(); Cx.pop();
        Y = Cy.front(); Cy.pop();
        Z = Cz.front(); Cz.pop();

        for(i = 0 ; i < 8 ; ++i)
        {
            xx = X + dx[i]; yy = Y + dy[i]; zz = Z + dz[i];
            if( xx > 0 && xx <= n && yy > 0 && yy <= n && zz > 0 && zz <= n && a[xx][yy][zz] == 0 )
            {
                a[xx][yy][zz] = a[X][Y][Z] + 1;
                Cx.push(xx);
                Cy.push(yy);
                Cz.push(zz);
            }

        }
    }

    printf("%d\n", a[n][n][n]);

    s = a[n][n][n]; pos = 1;

    while(pos <= s)
        for(i = 1 ; i <= n ; ++i)
            for(j = 1 ; j <= n ; ++j)
                for(l = 1 ; l <= n ; ++l)
                    if( a[i][j][l] == pos )
                    {
                        ++pos;
                        printf("%d %d %d\n", i, j, l);
                    }


}

int main()
{
    Read();
    Lee();
    return 0;
}
