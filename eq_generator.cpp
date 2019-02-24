/**
  *  Worg
  *  Test generator
  */
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;
FILE *fout=freopen("eq.in","w",stdout);

int main() {

    printf("10 100\n");
    for(int i = 1; i <= 10; ++i)
        printf("%d ", rand() % (1000000));
    printf("\n");
    int x, y;
    for(int i = 1; i <= 100; ++i) {

        x = rand() % 10 + 1;
        y = rand() % 10 + 1;
        if(x > y)
            swap(x, y);
        printf("%d %d\n", x, y);
    }

    return 0;
}
