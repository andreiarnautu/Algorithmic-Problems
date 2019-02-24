/**
  *  Worg
  */
#include <cstdio>

#define lsb(i) (i & (-i))

using namespace std;
FILE *fin = freopen("ecu.in", "r", stdin);
FILE *fout = freopen("ecu.out", "w", stdout);

const int MAX_LOG = 1 + 30;
const int MAX_N = 1 + 20;

/*-------- Input data --------*/
int N, M;
long double x[MAX_N], p[MAX_N], y[MAX_N];
/*-------- Algorithm data --------*/
long double mat[MAX_LOG][MAX_N][MAX_N], aux[MAX_N][MAX_N];
long double final_mat[MAX_N][MAX_N];
/*-------- --------*/

void read_input() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; i++) {
        scanf("%Lf", &x[i]);
    }
    for(int i = 1; i <= N; i++) {
        scanf("%Lf", &p[i]);
    }
    for(int i = 1; i <= N; i++) {
        scanf("%Lf", &y[i]);
    }
}

void multiply(long double A[][MAX_N], long double B[][MAX_N], long double to[][MAX_N]) {
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            for(int k = 1; k <= N; k++) {
                to[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void construct_initial_matrix() {
    for(int i = 1; i < N; i++) {
        mat[0][i][i] = p[i];
        mat[0][i][i + 1] = 1 - p[i + 1];
    }
    mat[0][N][N] = p[N];
    mat[0][N][1] = 1 - p[1];
}

void output_matrix() {

}

void build_matrix_levels() {
    for(int i = 1; (1 << i) <= M; i++) {
        multiply(mat[i - 1], mat[i - 1], mat[i]);
    }

    /* construim matricea finala a coeficientilor */
    int mask = M;
    int bit = 0;

    while((mask & (1 << bit)) == 0) {
        bit ++;
    }
    mask ^= (1 << bit);

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            final_mat[i][j] = mat[bit][i][j];
        }
    }

    while(mask) {
        while((mask & (1 << bit)) == 0) {
            bit ++;
        }
        mask ^= bit;

        multiply(mat[bit], final_mat, aux);
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                final_mat[i][j] = aux[i][j];
                aux[i][j] = 0;
            }
        }
    }
}

void write_output() {
    for(int i = 1; i <= N; i++) {
        double Solution = 0;
        for(int j = 1; j <= N; j++) {
            Solution += (double)final_mat[i][j] * x[j];
        }
        printf("%.3f\n", Solution);
    }
}

int main() {
    read_input();
    construct_initial_matrix();
    build_matrix_levels();
    write_output();
    return 0;
}
