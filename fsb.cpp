#include <cstdio>
#define A(i) A[i + 200000]
using namespace std;

FILE *fin=freopen("fsb.in","r",stdin);
FILE *fout=freopen("fsb.out","w",stdout);

int A[400003], n;
char s[200003];


int main()
{
    scanf("%d", &n); getchar(); gets(s);

    int i, sum = 0, sol = 0;

    A(0) = 1;

    for(i = 0; i < n ; ++i)
    {
        if( s[i] == '0' )
            --sum;
        else
            ++sum;
        ++A(sum);
        sol += A(sum) - 1;
    }

    printf("%d", sol);

}
