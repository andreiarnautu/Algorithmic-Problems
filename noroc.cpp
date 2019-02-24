/**
  *  Worg
  */
#include <cstdio>

FILE *fin = freopen("noroc.in", "r", stdin); FILE *fout = freopen("noroc.out", "w", stdout);

int main() {
    int X, M; scanf("%d%d", &X, &M);

    if(X > M) {
        printf("%.7f", 0);
    } else {
        printf("%.7f", 1 - (double)X / (double)M);
    }
	return 0;
}
