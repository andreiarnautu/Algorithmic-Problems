/**
  *  Worg
  */
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <ctime>

FILE *fin = freopen("adunare.in", "r", stdin);
FILE *fout = freopen("adunare.out", "w", stdout);

int main() {
  std::unordered_map<int, int > myMap;

  myMap[3] = 5;

  printf("%d\n", myMap[3]);

  clock_t startTime = clock();

  int a, b; scanf("%d %d", &a, &b);
  printf("%d\n", a + b);

  clock_t finishTime = clock();
  printf("Elapsed time: %.3f\n", (double)(finishTime - startTime) / CLOCKS_PER_SEC);

  return 0;
}
