/**
  *  Worg
  */
#include <cstdio>

using namespace std;

int main() {

    for(int i = 50; i <= 199; ++i)
        for(int j = 50; j <= 199; ++j) {
            printf("%d %d\n", i, j);
            fflush(stdout);
        }
    return 0;
}
