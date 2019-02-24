/**
  *   Worg
  **/
#include <stack>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define DIM 202
#define PII pair<int,int>
#define fi first
#define se second

using namespace std;
FILE *fin=freopen("bmatrix.in","r",stdin);
FILE *fout=freopen("bmatrix.out","w",stdout);

int A[DIM][DIM], S_down[DIM][DIM], S_up[DIM][DIM], Aux[DIM][DIM];
int Up[DIM], Down[DIM];
int n, m, best;
stack < PII > Q;
char S[DIM];

void Read()
{
    int i, j;
    scanf("%d %d ", &m, &n); // read data
    for(i = 1; i <= m; ++i)
    {
        gets(S);
        for(j = 1; j <= n; ++j)
            A[i][j] = S[j - 1] - '0';
    }

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
                                    // dynamic programming: when we find a shorter column of zeros than the one
                                    // in front of the queue, we erase it and update the maximum dimension of
                                    // the max-area rectangle.
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

        for(j = 1; j <= n; ++j)
        {
            last = j;
            while( !Q.empty() && S_down[i][ Q.top().fi ] > S_down[i][j] )
            {
                Down[i] = max( Down[i], S_down[i][ Q.top().fi ] * (j - Q.top().se) );
                last = Q.top().se;
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
            Q.pop();
        }
    }

    for(i = 1; i < m; ++i)         // update best
        best = max(best, Up[i] + Down[i + 1]);
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
}

int main()
{
    Read();
    Set();
    Solve();
    Rotate();
    Set();
    Solve();
    printf("%d", best);
    return 0;
}
