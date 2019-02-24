/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <vector>

FILE *fin = freopen("gauss.in", "r", stdin); FILE *fout = freopen("gauss.out", "w", stdout);

const double eps = 1e-8;

/*-------- Data --------*/
int N, M;
std::vector<std::vector<double > > sys;
/*-------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &M);

    sys = std::vector<std::vector<double > >(N, std::vector<double >(M + 1));

    for(int i = 0; i < N; i++) {
        for(int j = 0; j <= M; j++) {
            scanf("%lf", &sys[i][j]);
        }
    }
}

bool Null(double value) {
    return -eps < value && value < eps;
}

void Gauss() {
    std::vector<double > answer(M, 0.0);
    std::vector<int > pos(N, -1);

    for(int i = 0; i < N; i++) {
        for(int j = 0; j <= M; j++) {
            if(!Null(sys[i][j])) {
                pos[i] = j; break;
            }
        }

        if(pos[i] == -1) continue;
        if(pos[i] == M) {printf("Imposibil"); return;}

        for(int j = 0; j < N; j++) {
            if(i == j) continue;

            double coef = sys[j][pos[i]] / sys[i][pos[i]];
            for(int k = 0; k <= M; k++) {
                sys[j][k] -= coef * sys[i][k];
            }
        }
    }

    for(int i = 0; i < N; i++) {
        if(pos[i] != -1) {
            answer[pos[i]] = sys[i][M] / sys[i][pos[i]];
        }
    }

    for(auto& x : answer) {
        printf("%.12f ", x);
    }
    printf("\n");
}

int main() {
    ReadInput();

    Gauss();

    return 0;
}
