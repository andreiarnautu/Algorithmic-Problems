#include <cstdio>
using namespace std;
FILE *fin=freopen("patrat.in","r",stdin);
FILE *fout=freopen("patrat.out","w",stdout);

int F[20003];

int main()
{
    int i, j, x, y, cnt = 0;
    for(i = 1; i * i <= 20000; ++i)
        for(j = i + 1; j * j <= 20000 && j * j + i * i <= 20000; ++j)
            ++F[i * i + j * j];
    scanf("%d %d", &x, &y);
    for(i = x; i <= y ; ++i)
        if( F[i] > 1 )
        {
            printf("%d\n", i);
            ++cnt;
        }
    if( !cnt )
        printf("0");

    return 0;
}
