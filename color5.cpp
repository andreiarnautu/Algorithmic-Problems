/**
  *  Worg
  */
#include <cstdio>

FILE *fin = freopen("color5.in", "r", stdin); FILE *fout = freopen("color5.out", "w", stdout);

void AnswerTwo(const int N) {
    printf("2\n");
    for(int i = 0; i < N; i++) {
        printf("%d %d %d\n", i, (i + 1) % N, i % 2 + 1);
        if(i < N / 2) {
            printf("%d %d %d\n", i, N, 1);
        } else {
            printf("%d %d %d\n", i, N, 2);
        }
    }
}

void AnswerThree(const int N) {
    printf("3\n");
    for(int i = 0; i < N; i++) {
        printf("%d %d %d\n", i, (i + 1) % N, 3);
        printf("%d %d %d\n", i, N, i % 2 + 1);
    }
}

int main() {
    int N; scanf("%d", &N);

    if(N <= 6) {
        AnswerTwo(N);
    } else {
        AnswerThree(N);
    }
	return 0;
}
