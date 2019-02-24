#include <cstdio>
#include <cstring>
using namespace std;

FILE *fin=freopen("doi.in","r",stdin);
FILE *fout=freopen("doi.out","w",stdout);

int A[501];
char s[502];

void Read()
{
    int i, k;
    gets(s);
    A[0] = strlen(s);

    for(i = A[0], k = 0; i > 0; --i, ++k)
        A[i] = s[k] - 48;
}

void Divide()
{
    int i, t = 0;
    for(i = A[0]; i > 0; --i, t %= 2)
        A[i] = (t = t * 10 + A[i]) / 2;
    for(; A[0] > 1 && !A[A[0]]; --A[0]);
}

void Raise(int t)
{
    int i;
    for(i = 1 ; i <= A[0] && t != 0 ; ++i, t /= 10)
        A[i] = (t += A[i]) % 10;
    if(t)
    {
        ++A[0];
        A[A[0]] = t;
    }

}

void Solve()
{
    int cnt = 0;

    while( !(A[0] == 1 && A[1] == 0) )
    {
        if((A[1] + A[2] * 10) % 4 == 1 || (A[0] == 1 && A[1] == 3) )
            Raise(-1);
        else if((A[1] + A[2] * 10) % 4 == 3)
            Raise(1);
        else
            Divide();
        ++cnt;
    }

    printf("%d\n", cnt);
}

int main()
{
    int t;
    scanf("%d", &t); getchar();
    for(; t > 0 ; --t)
    {
        Read();
        Solve();
    }
}
