/**
  *   Worg
  **/
#include <stack>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define DIM 1010
#define PII pair<int,int>
#define fi first
#define se second
#define buffDIM 100000

using namespace std;
FILE *fin=freopen("cladiri.in","r",stdin);
FILE *fout=freopen("cladiri.out","w",stdout);

char buff[buffDIM];
int pos, m, n, h, w, best;
int A[DIM][DIM], S_down[DIM][DIM], S_up[DIM][DIM], Aux[DIM][DIM], Up[DIM], Down[DIM];
stack < PII > Q;

void read(int &x) // parse the file
{
    x = 0;
    while( buff[pos] < '0' || buff[pos] > '9' )
        if( ++pos == buffDIM )
        {
            fread(buff, 1, buffDIM, stdin);
            pos = 0;
        }

    while( buff[pos] >= '0' && buff[pos] <= '9' )
    {
        x = x * 10 + buff[pos] - '0';
        if( ++pos == buffDIM )
        {
            fread(buff, 1, buffDIM, stdin);
            pos = 0;
        }
    }
}

void Read_Data()
{
    read(m); read(n); read(w); read(h);
    int i, j;
    for(i = 1; i <= m; ++i)
        for(j = 1; j <= n; ++j)
            read( A[i][j] );
}

void Set()
{
    int i, j;               // construct S_up and S_down( self-explanatory )
    memset(S_up, 0, sizeof(S_up));
    memset(S_down, 0, sizeof(S_down));

    for(i = 1; i <= m; ++i)
        {
            for(j = 1; j <= n; ++j)
                if( A[i][j] == 0 )
                    S_up[i][j] = S_up[i - 1][j] + 1;
                else
                    S_up[i][j] = 0;
        }

    for(i = m; i ; --i)
        {
            for(j = 1; j <= n; ++j)
                if( A[i][j] == 0 )
                    S_down[i][j] = S_down[i + 1][j] + 1;
                else
                    S_down[i][j] = 0;
        }
}

void Solve()
{
    int i, j, last;
    memset(Up, 0, sizeof(Up));      // initializing arrays
    memset(Down, 0, sizeof(Down));
    bool ok;

    for(i = 1; i <= m; ++i)
    {
        Up[i] = Up[i - 1];          // for Up

        for(j = 1; j <= n; ++j)
        {
            last = j;
            while( !Q.empty() && S_up[i][ Q.top().fi ] > S_up[i][j] )
            {
                Up[i] = max( Up[i], S_up[i][ Q.top().fi ] * (j - Q.top().se) );
                last = Q.top().se;
                Q.pop();
            }
            if( S_up[i][j] == 0 )
                continue;
            if( Q.empty() )
                Q.push(make_pair(j, last));
            else
            {
                if( S_up[i][Q.top().fi] < S_up[i][j] )
                    Q.push(make_pair(j, last));
            }
        }
        while( !Q.empty() )
        {
            Up[i] = max( Up[i], S_up[i][ Q.top().fi ] * (n + 1 - Q.top().se) );
            Q.pop();
        }
    }

    for(i = m; i; --i)
    {
        Down[i] = Down[i + 1];      // for Down
        ok = 0;

        for(j = 1; j <= n; ++j)
        {
            last = j;
            while( !Q.empty() && S_down[i][ Q.top().fi ] > S_down[i][j] )
            {
                Down[i] = max( Down[i], S_down[i][ Q.top().fi ] * (j - Q.top().se) );
                last = Q.top().se;
                if( S_down[i][ Q.top().fi ] >= h && j - Q.top().se >= w )
                    ok = 1;

                Q.pop();
            }
            if( S_down[i][j] == 0 )
                continue;
            if(Q.empty())
                Q.push( make_pair(j, last) );
            else
            {
                if( S_down[i][Q.top().fi] < S_down[i][j] )
                    Q.push( make_pair(j, last) );
            }
        }

        while( !Q.empty() )
        {
            Down[i] = max( Down[i], S_down[i][ Q.top().fi ] * (n + 1 - Q.top().se) );
            if( S_down[i][ Q.top().fi ] >= h && (n + 1 - Q.top().se) >= w )
                ok = 1;

            Q.pop();
        }

        if( ok )
        {
            best = max(best, Down[i + h]);
            best = max(best, Up[i - 1]);
        }
    }
}

void Rotate()
{
    int i, j;
    for(j = n; j; --j)
        for(i = 1; i <= m; ++i)
            Aux[n - j + 1][i] = A[i][j];

    for(i = 1; i <= n; ++i)
        for(j = 1; j <= m; ++j)
            A[i][j] = Aux[i][j];
    swap(n, m);
    swap(h, w);
}

int main()
{
    Read_Data();
    Set();
    Solve();
    Rotate();
    Set();
    Solve();
    printf("%d", best);
    return 0;
}
