// Genereaza teste
#include <cstdio>
using namespace std;
FILE *fout = freopen("stalpi.in","w",stdout);

int main()
{
    int i;
    printf("100000\n");
    for(i = 1; i <= 100000; ++i)
    {
        printf("%d %d %d %d\n", i * 10, 100000 - i + 1, 1000000000, 1000000000);
    }
    return 0;
}
