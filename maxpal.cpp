/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("maxpal.in", "r", stdin);
FILE *fout = freopen("maxpal.out", "w", stdout);

const int mod = 666013;

/*-------- Input data --------*/
int N;
vector< int > vec;
/*-------- Algorithm data --------*/
vector< int > size_A, size_B, size_C;
vector< int > count_A, count_B, count_C;
int delay;
/*-------- --------*/

void read_input() {
    scanf("%d", &N);
    vec.resize(N + 1);
    size_A.resize(N + 1); count_A.resize(N + 1);
    size_B.resize(N + 1); count_B.resize(N + 1);
    size_C.resize(N + 1); count_C.resize(N + 1);

    for(int i = 1; i <= N; i++) {
        scanf("%d", &vec[i]);
    }
}

void initialize_first_diags() {
    for(int i = 1; i <= N; i++) {               /* Diagonala principala */
        size_A[i] = 1;
        count_A[i] = 1;
    }

    for(int i = 1; i < N; i++) {                /* Diagonala de imediat de deasupra diagonalei principale */
        if(vec[i] == vec[i + 1]) {
            size_B[i] = 2; count_B[i] = 1;
        } else {
            size_B[i] = 1; count_B[i] = 2;
        }
    }
}

void construct_diags(int delay = 2) {
    for(int i = 1; i <= N - delay; i++) {                   /* Calculam intai lungimea maxima a subsirului */
        if(vec[i] == vec[i + delay]) {
            size_C[i] = 2 + size_A[i + 1];
        } else {
            size_C[i] = max(size_B[i], size_B[i + 1]);
        }
    }

    for(int i = 1; i <= N - delay; i++) {                   /* Apoi calculam numarul de moduri de a ajunge la acea lungime */
        count_C[i] = 0;
        if(vec[i] == vec[i + delay]) {
            count_C[i] = count_A[i + 1];
        }
        if(size_C[i] == size_B[i + 1]) {
            count_C[i] += count_B[i + 1];
        }
        if(size_C[i] == size_B[i]) {
            count_C[i] += count_B[i];
        }
        if(size_C[i] == size_A[i + 1]) {
            count_C[i] -= count_A[i + 1];
        }

        if(count_C[i] < 0) {
            count_C[i] += mod;
        } else {
            count_C[i] %= mod;
        }
    }

    size_A = size_B; size_B = size_C;
    count_A = count_B; count_B = count_C;
    if(delay < N - 1) {
        construct_diags(delay + 1);
    }
}

int main() {
    read_input();
    initialize_first_diags();
    construct_diags();
    printf("%d %d\n", size_B[1], count_B[1]);
    return 0;
}
