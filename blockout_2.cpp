#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
FILE *fin = freopen("blockout.in", "r", stdin);
FILE *fout = freopen("blockout.out", "w", stdout);
int H[111][111], N, M, h, R, X[111][111];

int Check(int x1, int y1, int x2, int y2)
{
    int Max = 0, a, b, c, d;
    a = x1 / R;
    if(x1 % R != 0)
        ++a;
    b = y1 / R;
    if(y1 % R != 0 )
        ++b;
    c = x2 / R;
    //if( x2 % R != 0 )
//        --c;
    d = y2 / R;
   // if( y2 % R != 0 )
    //    --d;
    for(int i = a ; i <= c ; ++i )
        for(int j = b ; j <= d ; ++j )
            if( X[i][j] > Max )
                Max = X[i][j];

        for(int i = x1 ; i < a * R ; ++i )
            for(int j = y1 ; j <= y2 ; ++j )
                if( H[i][j] > Max )
                    Max = H[i][j];
        for(int i = c * R + 1 ; i <= x2 ; ++i )
            for(int j = y1 ; j <= y2 ; j++ )
                if( H[i][j] > Max )
                    Max = H[i][j];

        for(int i = a * R ; i < (c + 1) * R ; ++i )
            for(int j = y1 ; j <= b * R ; ++j )
                if( H[i][j] > Max )
                    Max = H[i][j];

        for(int i = a * R ; i < (c + 1) * R ; ++i )
            for(int j = R * (d + 1) ; j <= y2 ; j++ )
                if( H[i][j] > Max )
                    Max = H[i][j];

    return Max;
}

void Plus(int x1, int y1, int x2, int y2, int Val)
{
    int i, j;
    for(i = x1 ; i <= x2 ; ++i )
        for( j = y1 ; j <= y2 ; ++j )
            H[i][j] = Val + h;
    int a, b, c, d;
    a = x1 / R;
    if(x1 % R != 0)
        ++a;
    b = y1 / R ;
    if(y1 % R != 0 )
        ++b;
    c = x2 / R ;
    //if( x2 % R != 0 )
        --c;
    d = y2 / R;
   // if( y2 % R != 0 )
     //   --d;
    for(int i = a ; i <= c ; ++i )
        for(int j = b ; j <= d ; ++j )
            X[i][j] = Val + h;


  /*  if( (x1 - 1 ) % R != 0 && (y1 - 1) % R != 0 )
        X[a - 1][b - 1] = Val + h;

    if( (y1 - 1) % R != 0 )
        for(int i = a ; i <= c ; i++ )
            X[i][b - 1] = Val + h;

    if( (y1 - 1) % R != 0 && x2 % R != 0)
        X[c + 1][b - 1] = Val + h;

    if( x2 % R != 0 )
        for(int j = b ; j <= d ; ++j )
            X[c + 1][j] = Val + h;

    if( x2 % R != 0 && y2 % R != 0 )
        X[c + 1][d + 1] = Val + h;

    if( y2 % R != 0 )
        for(int i = a ; i <= c ; ++i )
            X[i][d + 1] = Val + h;

    if( (x1 - 1) % R != 0 && y2 != 0 )
        X[a - 1][d + 1] = Val + h;

    if( (x1 % R != 0 && a > 0)
        for(int i = b ; i <= d ; ++i )
            X[a - 1][i] = Val + h; */
}

void Solve()
{
    int x1, y1, x2, y2, k;
    R = sqrt((double) N );
    for(int i = 1; i <= M ; ++i )
    {
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &h);
        k = Check(x1, y1, x2, y2);
        printf("%d\n", k);
        Plus(x1, y1, x2, y2, k);
    }

}

int main()
{
    scanf("%d%d", &N, &M);
    Solve();
}
