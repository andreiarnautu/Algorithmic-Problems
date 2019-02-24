#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin=freopen("mere2.in","r",stdin);
FILE *fout=freopen("mere2.out","w",stdout);
int A, B, C, Dif, Type, AA, BB, CC;


int main()
{
    scanf("%d%d%d", &A, &B, &C);
    if( ( A + B + C) % 3 != 0 )
    {
        printf("-1\n-1 -1 -1");
        return 0;
    }

    AA = A;
    BB = B;
    CC = C;

    if( C > B )
        swap( B , C );
    if( B > A )
        swap( A , B );
    if( C > B )
        swap( B , C );
    if( A - B > B - C )
    {
        Dif = B - C;
        Type = 2;
    }
    else
    {
        Dif = A - B;
        Type = 1;
    }

    if( Dif == 0 )
    {
        if( Type == 1 )
        {
            int Steps;
            Steps = abs( A - C ) / 3 * 2;
            C -= Steps;
            if( C < 0 )
            {
                printf("-1\n-1 -1 -1");
                return 0;
            }
            printf("%d\n", Steps);
            printf("%d %d %d", AA - C, BB - C , CC - C);
            return 0;
        }

        if( Type == 2 )
        {
            int Steps;
            Steps = abs( A - C ) / 3 * 2;
            A -= 3 * Steps;
            if( CC - A < 0 )
            {
                printf("-1\n-1 -1 -1");
                return 0;
            }
            printf("%d\n", Steps);
            printf("%d %d %d", AA - A , BB - A , CC - A);
            return 0;
        }
    }

    if( Type == 1 )
    {
        int Sol;
        Sol = Dif;
        A -= 3 * Dif;
        B -= 2 * Dif;
        C -= Dif;

        Dif = A - C;
        int Steps;
        Steps = Dif / 3 * 2;
        C -= Steps;
        A -= (Steps + 3 * Steps / 2);
        B -= (Steps + 3 * Steps / 2);
        if( A < 0 || B < 0 || C < 0 )
        {
            printf("-1\n-1 -1 -1");
            return 0;
        }
        else
        {
            printf("%d\n", Sol + Steps);
            printf("%d %d %d", AA - A, BB - A, CC - A);
        }
    }

    if( Type == 2 )
    {
        int Sol;
        Sol = Dif;
        A -= 3 * Dif;
        B -= 2 * Dif;
        C -= 1 * Dif;
        Dif = A - C;
        int Steps;
        Steps = Dif / 3 * 2;
        C -= Steps / 2 * 3;
        B -= Steps / 2 * 3;
        A -= Steps * 3;;
        if( A < 0 || B < 0 || C < 0 )
        {
            printf("-1\n-1 -1 -1");
            return 0;
        }
        printf("%d\n", Sol + Steps);
        printf("%d %d %d", AA - A , BB - B, CC - C);
    }

    return 0;
}
