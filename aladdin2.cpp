#include <cstdio>
#include <cstring>
#define DIM 10000
using namespace std;
FILE *fin=freopen("aladdin2.in","r",stdin);
FILE *fout=freopen("aladdin2.out","w",stdout);

int n, m;

class Huge
{
    public:

        int A[DIM];

        Huge()
        {
            memset(A, 0, sizeof(A));
        }

        inline void Set_One()
        {
            A[1] = A[0] = 1;
        }

        inline void operator *= (int k)
        {
            int i, t = 0;
            for(i = 1; i <= A[0] || t; ++i, t /= 10)
                A[i] = (t += A[i] * k) % 10;
            A[0] = i - 1;
        }

        inline void operator -= (Huge q)
        {
            int i, t = 0;

            for(i = 1; i <= A[0]; ++i)
            {
                A[i] -= ((i <= q.A[0]) ? q.A[i] : 0) + t;
                A[i] += (t = A[i] < 0) * 10;
            }
            for(; A[0] > 1 && !A[A[0]]; --A[0]);
        }

        inline void operator += (Huge q)
        {
            int i, t;
            for(i = 1, t = 0; i <= q.A[0] || i <= A[0] || t; t /= 10, ++i)
                A[i] = (t += A[i] + q.A[i] ) % 10;
            A[0] = i - 1;
        }

        void write()
        {
            for(int i = A[0]; i > 0; --i)
                printf("%d", A[i]);
            printf("\n");
        }
};

void Solve()
{
    Huge a, b, c;
    int x, y;

    a.Set_One();
    x = m / 20;
    y = m % 20;
    for(int i = 1; i <= x; ++i)
        a *= 1048576;
    for(int i = 1; i <= y; ++i)
        a *= 2;

    b.Set_One(), b.A[1] = 2;
    a -= b;

    c.Set_One();
    x = n / 20;
    y = n % 20;
    for(int i = 1; i <= x; ++i)
        c *= 1048576;
    for(int i = 1; i <= y; ++i)
        c *= 2;

    a += c;
    a.write();

}

int main()
{
    scanf("%d %d", &m, &n);
    Solve();
    return 0;
}
