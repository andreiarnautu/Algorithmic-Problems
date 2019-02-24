/*
    How about a coding trick?
*/
#include <cstdio>
#include <utility>
#include <algorithm>
#define DIM 509
#define INF 2000000000
#define PII pair<int,int>
#define fi first
#define se second
using namespace std;
FILE *fin=freopen("lenes.in","r",stdin);
FILE *fout=freopen("lenes.out","w",stdout);

int A[DIM][DIM];
int V[DIM * 5], S[DIM];
int m, n, k1, k2, op;
vector < PII > Down, Up;

void Read()
{
    scanf("%d", &op);
    scanf("%d %d %d %d", &m, &n, &k1, &k2);
    for(int i = 1; i <= m; ++i)
        for(int j = 1; j <= n; ++j)
            scanf("%d", &A[i][j]);
}

void Sort_Columns()
{
    int i, j;

    for(j = 1; j <= n; ++j)
    {
        for(i = 1; i <= m; ++i)
            V[i] = A[i][j], S[j] += A[i][j];
        sort(V + 1, V + m + 1);
        for(i = 1; i <= m; ++i)
            A[i][j] = V[i];
    }

    for(int i = 1; i <= m; ++i)
        A[i][0] = A[i][n + 1] = DIM * 10;
}

void Solve_1()
{
    int p1, p2, elem, i, j, best = INF, sum, val1, val2;

    for(j = 1; j <= n; ++j)
    {
        sum = val1 = val2 = 0;
        sum = S[j];

        p1 = p2 = 1, elem = 0;
        while( elem < k1 )
        {
            if( A[p1][j - 1] <= A[p2][j + 1] )
                sum += A[p1][j - 1], ++p1;
            else
                sum += A[p2][j + 1], ++p2;
            ++elem;
        }
        best = min(best, sum);
    }
    printf("%d\n", best);
}

void Up_and_Down()
{
    int i, j, sum, p1, p2, k;
    PII aux;

    for(j = 1; j <= n; ++j)
    {
        sum = S[j], p1 = p2 = 1, k = k1;
        while( k )
        {
            if( A[p1][j - 1] < A[p2][j + 1] )
                sum += A[p1][j - 1], ++p1;
            else
                sum += A[p2][j + 1], ++p2;
            --k;
        }
        Down.push_back( make_pair(sum, j) );
    }

    for(j = 1; j <= n; ++j)
    {
        sum = S[j], p1 = p2 = 1, k = k2;
        while( k )
        {
            if( A[p1][j - 1] < A[p2][j + 1] )
                sum += A[p1][j - 1], ++p1;
            else
                sum += A[p2][j + 1], ++p2;
            --k;
        }
        Up.push_back( make_pair(sum, j) );
    }

    sort(Down.begin(), Down.end());
    sort(Up.begin(), Up.end());
}

inline int Sticky_Columns()
{
    int ret = INF, i, j, sum, k1_1, k1_2, k2_1, k2_2, optim;

    for(j = 2; j < n - 1; ++j)
    {
        sum = S[j] + S[j + 1];
        k1_1 = k1_2 = k2_1 = k2_2 = 0;
        for(i = 1; i <= k1; ++i)
            k1_1 += A[i][j - 1], k1_2 += A[i][j + 2];
        for(i = 1; i <= k2; ++i)
            k2_1 += A[i][j - 1], k2_2 += A[i][j + 2];

        optim = min(k1_1 + k2_2, k1_2 + k2_1);
        ret = min(ret, optim + sum);
    }
    return ret;
}

inline int Dist2_Columns(int K1, int K2)
{
    int i, j, p1, p2, ret = INF, sum, R;

    if( n == 3 )
    {
        ret = S[1] + S[3];
        for(i = 1; i <= K1 + K2; ++i)
            ret += A[i][2];
        return ret;
    }

    sum = S[1] + S[3];
    for(i = 1; i <= K1; ++i)
        sum += A[i][2];
    p1 = K1 + 1, p2 = 1;
    R = K2;
    while( R && p1 <= m )
    {
        if( A[p1][2] < A[p2][4] )
            sum += A[p1][2], ++p1;
        else
            sum += A[p2][4], ++p2;
        --R;
    }
    while( R )
        sum += A[p2][4], --R, ++p2;

    ret = sum;

    sum = S[n] + S[n - 2];
    for(i = 1; i <= K2; ++i)
        sum += A[i][n - 1];
    p1 = 1, p2 = K2 + 1;
    R = K1;
    while( R && p2 <= m )
    {
        if( A[p1][n - 3] <= A[p2][n - 1] )
            sum += A[p1][n - 3], ++p1;
        else
            sum += A[p2][n - 1], ++p2;
        --R;
    }
    while( R )
        sum += A[p1][n - 3], ++p1, --R;

    ret = min(ret, sum);

    for(i = 1; i <= K1 + K2 + 1; i++)
        V[i] = 0;

    for(i = 2; i + 3 <= n; ++i)
    {
        sum = S[i] + S[i + 2];
        p1 = 1, p2 = 1;
        while(p1 <= K1 && p2 <= K2)
        {
            if( A[p1][i - 1] < A[p2][i + 3] )
                V[p1 + p2 - 1] = A[p1][i - 1], ++p1;
            else
                V[p1 + p2 - 1] = A[p2][i + 3], ++p2;
        }
        while(p1 <= K1)
            V[p1 + p2 - 1] = A[p1][i - 1], ++p1;
        while(p2 <= K2)
            V[p1 + p2 - 1] = A[p2][i + 3], ++p2;


        p1 = 1, p2 = K1 + K2;
        while( A[p1][i + 1] < V[p2] && p1 <= m )
        {
            V[p2] = A[p1][i + 1];
            --p2, ++p1;
        }

        for(j = 1; j <= K1 + K2; ++j)
            sum += V[j];
        ret = min(ret, sum);
        //printf("%d ", sum);
    }
    return ret;
}

void Solve_2()
{
    int i, j, optim = INF;
    Up_and_Down();
    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < n; ++j)
            if( abs( Down[i].se - Up[j].se ) >= 3 )
            {
                optim = min(optim, Down[i].fi + Up[j].fi);
                break;
            }
    }
    optim = min( optim, Sticky_Columns() );
    optim = min( optim, Dist2_Columns(k1, k2) );
    optim = min( optim, Dist2_Columns(k2, k1) );
    printf("%d", optim);
}

int main()
{
    Read();
    Sort_Columns();
    if(op == 1)
        Solve_1();
    else
        Solve_2();
    return 0;
}
