// It's not the load that breaks you down, it's the way you carry it.
#include <cstdio>
#include <cstring>
#include <ctime>
#include <algorithm>
using namespace std;
FILE *fin=freopen("ech.in","r",stdin);
FILE *fout=freopen("ech.out","w",stdout);

char S[30];

class Huge
{
    public:

        int A[30];

        Huge()
        {
            memset(A, 0, sizeof(A));
        }

        inline void make(int val)
        {
            for(int i = 1; i <= A[0]; ++i)
                A[i] = 0;
            A[0] = 0;

            while( val )
            {
                ++A[0];
                A[A[0]] = val % 10;
                val /= 10;
            }
        }

        inline void read()
        {
            gets(S);
            A[0] = strlen(S);
            for(int i = A[0]; i > 0; --i)
                A[i] = S[ A[0] - i ] - 48;
        }

        inline int rest(int val)
        {
            int i, t = 0;
            for(i = A[0]; i > 0; --i)
                t = (t * 10 + A[i]) % val;
            return t;
        }

        inline void add( Huge q )
        {
            int i, t;
            for(i = 1, t = 0; i <= q.A[0] || i <= A[0] || t; ++i, t /= 10)
            {
                A[i] = (t += A[i] + q.A[i]) % 10;
                if( i > q.A[0] && t < 10 )
                {
                    i = max(i + 1, A[0] + 1);
                    //--i;
                    break;
                }
                /*if( i >= q.A[0] && t < 10 )//(t / 10 + A[i + 1] < 10 && !(i >= A[0] && t >= 10) ))
                {
                    i = A[0] + 1;
                    break;
                }*/
            }
            A[0] = i - 1;
        }

        inline bool ech()
        {
            int sum1 = 0, sum2 = 0;
            for(int i = 1; i <= A[0]; ++i)
            {
                if( i % 2 == 1 )
                    sum1 += A[i];
                else
                    sum2 += A[i];
            }

            return (sum1 == sum2);
        }

        inline void write()
        {
            for(int i = A[0]; i > 0; --i)
                printf("%d", A[i]);
            printf("\n");
        }

};

void Solve()
{
    clock_t start, stop;
    start = clock();

    Huge x, y;
    int rest;

    x.read();
    rest = x.rest(11);

    y.make(11 - rest);

    x.add(y);
    //x.write();
    y.make(11);

    while( !x.ech() )
        x.add(y);

    x.write();

    stop = clock();

    printf("\n%.4f", (double)(stop - start) / CLOCKS_PER_SEC);

}

int main()
{
    Solve();
    return 0;
}
