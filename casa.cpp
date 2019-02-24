/*
    How about a coding trick?
*/
#include <cstdio>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
#define PII pair<int,int>
#define fi first
#define se second
using namespace std;
FILE *fin=freopen("casa.in","r",stdin);
FILE *fout=freopen("casa.out","w",stdout);

vector < PII > coord;
vector < int > M[100010], order[100010];
queue < PII > Q;
int ord[30];

void Solve_1()
{
    int n, x, y, xmin, ymin, xmax, ymax;
    scanf("%d", &n);
    coord.push_back( make_pair(0, 0) );
    coord.push_back( make_pair(1, 1) );

    char c;
    int last;

    xmin = ymin = xmax = ymax = 1;
    for(int i = 2; i <= n; ++i)
    {
        scanf("%d %c", &last, &c);
        x = coord[last].fi;
        y = coord[last].se;
        if( c == 'E' )
            ++y;
        else if( c == 'S' )
            ++x;
        else if( c == 'V' )
            --y;
        else if( c == 'N' )
            --x;
        coord.push_back( make_pair(x, y) );
        xmin = min(xmin, x);
        ymin = min(ymin, y);
        xmax = max(xmax, x);
        ymax = max(ymax, y);
    }

    int L = 0, C = 0;
    if( xmin < 1 )
        L = 1 - xmin;
    if( ymin < 1 )
        C = 1 - ymin;
    xmax += L, ymax += C;
    printf("%d %d\n", xmax, ymax);

    for(int i = 1; i <= xmax; ++i)
        M[i].reserve(ymax + 1);
    for(int i = 1; i <= xmax; ++i)
        for(int j = 1; j <= ymax; ++j)
            M[i][j] = 0;

    for(int i = 1; i <= n; ++i)
    {
        coord[i].fi += L, coord[i].se += C;
        M[ coord[i].fi ][ coord[i].se ] = 1;
    }
    for(int i = 1; i <= xmax; ++i)
    {
        for(int j = 1; j <= ymax; ++j)
            printf("%d ", M[i][j]);
        printf("\n");
    }
}

void Solve_2()
{
    int m, n, i, j, nr = 0;

    scanf("%d %d", &m, &n);

    for(i = 0; i <= m + 1; ++i)
        {
            M[i].reserve(n + 2);
            order[i].reserve(n + 2);
            for(j = 0; j <= n + 1; ++j)
                M[ i ][ j ] = 0;
        }

    for(i = 1; i <= m; ++i)
        for(j = 1; j <= n; ++j)
        {
            scanf("%d", &M[i][j]);
            if( M[i][j] )
                ++nr;
        }

    printf("%d ", nr);

    for(j = 1; j <= n; ++j)
    {
        if( M[1][j] )
            break;
    }

    printf("%d\n", j);

    Q.push( make_pair(1, j) );
    M[1][j] = 0;
    order[1][j] = 1;
    int camera = 1;

    while( !Q.empty() )
    {
        PII vf = Q.front(); Q.pop();
        int x = vf.fi, y = vf.se;

        if( M[ x ][ y + 1 ] )
        {
            M[ x ][ y + 1 ] = 0;
            printf("%d E\n", order[ x ][ y ]);
            order[ x ][ y + 1 ] = (++camera);
            Q.push( make_pair(x, y + 1) );
        }

        if( M[ x - 1 ][ y ] )
        {
            M[ x - 1 ][ y ] = 0;
            printf("%d N\n", order[ x ][ y ]);
            order[ x - 1 ][ y ] = (++camera);
            Q.push( make_pair(x - 1, y) );
        }

        if( M[ x + 1 ][ y ] )
        {
            M[ x + 1 ][ y ] = 0;
            printf("%d S\n", order[ x ][ y ]);
            order[ x + 1 ][ y ] = (++camera);
            Q.push( make_pair(x + 1, y) );
        }

        if( M[ x ][ y - 1 ] )
        {
            M[ x ][ y - 1 ] = 0;
            printf("%d V\n", order[ x ][ y ]);
            order[ x ][ y - 1 ] = (++camera);
            Q.push( make_pair(x, y - 1) );
        }
    }
}

int main()
{
    int op;
    scanf("%d", &op);
    if( op == 1 )
        Solve_1();
    else
        Solve_2();

    return 0;
}
