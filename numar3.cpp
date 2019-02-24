#include <cstdio>
#include <cstring>
#define DIM 4004
using namespace std;
FILE *fin=freopen("numar3.in","r",stdin);
FILE *fout=freopen("numar3.out","w",stdout);

class Huge
{
    public:
        int A[DIM];

        Huge(int len)
        {
            memset(A, 0, sizeof(A));
            A[0] = len;
        }

        inline bool mod2()
        {
            return (A[1] % 2 == 0);
        }

        inline bool mod5()
        {
            return (A[1] % 5 == 0);
        }

        void operator /= (int divizor)
        {
            int i, t = 0;
            for(i = A[0]; i > 0; --i, t %= divizor )
                A[i] = (t = t * 10 + A[i]) / divizor;
            for( ; A[0] > 1 && !A[A[0]]; --A[0] );
        }

        void mult(Huge q, Huge rez)
        {
            int i, j, t;
            memset(rez.A, 0, sizeof(rez.A));

            for(i = A[0]; i > 0; --i)
            {
                for(t = 0, j = 1; j <= q.A[0]; ++j, t /= 10)
                    rez.A[i + j - 1] = (t += rez.A[i + j - 1] + A[i] * q.A[j]) % 10;
                if( i + j - 2 > rez.A[0])
                    rez.A[0] = i + j - 2;
            }

        }


        void Write()
        {
            for(int i = A[0]; i > 0; --i)
                printf("%d", A[i]);
            printf("\n");
        }

};

int ni, nz;

void Read_and_Solve()
{
    scanf("%d %d ", &ni, &nz);
    Huge x(ni + nz), y(nz + 1);

    y.A[nz + 1] = 1;

    for(int i = 0; i < ni + nz; ++i)
        scanf("%d", &x.A[ni + nz - i]);

    while( x.mod2() && y.mod2() )
    {
        x /= 2;
        y /= 2;
    }

    while( x.mod5() && y.mod5() )
    {
        x /= 5;
        y /= 5;
    }

    printf("%d\n", x.A[0]);
    x.Write();
    printf("%d\n", y.A[0]);
    y.Write();

}

int main()
{
    Read_and_Solve();
    return 0;
}
