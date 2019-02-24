/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("cpr.in", "r", stdin);
FILE *fout = freopen("cpr.out", "w", stdout);

/*-------- Input data --------*/
int N;
/*-------- --------*/

void solve_general(int k) {
    /* primii 3 pasi sunt pentru a aduce sirul intr-o forma convenabila */
    printf("%d %d %d\n", 1, 2, (k + 3) / 2);

    printf("%d %d %d\n", 2, k, 3);

    printf("%d %d %d\n", k, 4, 0);

    for(int left = k - 1, right = 5; left > right; left--, right++) {
        printf("%d %d %d\n", left, right, left + 1);
    }
}

int main() {
    scanf("%d", &N);
    if(N == 1) {
        printf("0\n");
    } else if(N == 2) {
        printf("1\n");
        printf("2 2 0\n");
    } else if(N == 3) {
        printf("2\n");
        printf("2 3 1\n");
        printf("3 2 1\n");
    } else {
        printf("%d\n", 1 + (N / 2));
        if(N % 2 == 1) {
            solve_general(N);
        } else {
            solve_general(N - 1);
            printf("%d %d 0\n", N, N);
        }
    }
    return 0;
}
