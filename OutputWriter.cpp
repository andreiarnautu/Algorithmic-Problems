/**
  *  Worg
  *  Mar 11, 2018
  *  11:52:07 PM
  */
#include <ctime>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fout = freopen("smooth2.in", "w", stdout);

int main() {
  clock_t startTime = clock();

  const int n = 1000;
  const int m = 1000;

  printf("%d %d\n", n, m);
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      printf("%d ", 1);
    }
    printf("\n");
  }

  clock_t finishTime = clock();

  printf("Execution time: %.3f ms\n", (double)(finishTime - startTime) / CLOCKS_PER_SEC);

  return 0;
}
