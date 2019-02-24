/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("flux.in", "r", stdin); FILE *fout = freopen("flux.out", "w", stdout);

const int kMaxN = 100 + 5;
const double eps = 1e-8;

/*------- Input data -------*/
int N, M;
std::vector<std::vector<std::pair<int, int > > > graph;
/*------- Gauss -------*/
std::vector<std::vector<double > > sys;
std::vector<double > sol;
/*------- -------*/

void ReadInput() {
    scanf("%d%d", &N, &M);

    graph = std::vector<std::vector<std::pair<int, int > > >(N + 5);
    sys = std::vector<std::vector<double > > (N + 5, std::vector<double > (N + 5, 0.0));
    sol = std::vector<double >(N + 5, 0.0);

    for(int i = 1; i <= M; i++) {
        int u, v, c; scanf("%d%d%d", &u, &v, &c);
        graph[u].push_back({v, c}); graph[v].push_back({u, c});
    }
}

void BuildEquationSystem() {
    sys[1][1] = 1.0;
    sys[N][N] = sys[N][N + 1] = 1.0;

    for(int i = 2; i < N; i++) {
        for(auto& edge : graph[i]) {
            sys[i][i] -= 1.0;
            sys[i][edge.first] += 1.0;
        }
    }
}

bool IsNull(double value) {
    return -eps < value && value < eps;
}

void Gauss() {
    int i = 1, j = 1;

    while(i <= N && j <= N) {
        int k = i;
        while(k <= N && IsNull(sys[k][j])) {
            k ++;
        }

        if(k <= N) {
            swap(sys[i], sys[k]);
            for(int k = N + 1; k >= j; k--) {  //  Divide line values by sys[i][j]
                sys[i][k] /= sys[i][j];
            }

            for(int line = i + 1; line <= N; line ++) {
                for(int col = N + 1; col >= j; col--) {
                    sys[line][col] -= sys[line][j] * sys[i][col];
                }
            }

            i ++;
        } else {
            j ++;
        }
    }

    //  Get solution
    for(int i = N; i >= 1; i--) {
        for(j = 1; j <= N + 1 && IsNull(sys[i][j]); j++);

        if(j <= N) {
            sol[j] = sys[i][N + 1];
            for(int k = j + 1; k <= N; k++) {
                sol[j] -= sol[k] * sys[i][k];
            }
        }
    }
}

double GetSolution() {
    double coef = 1e12;

    for(int i = 1; i <= N; i++) {
        for(auto& edge : graph[i]) {
            if(sol[edge.first] - sol[i] >= 0) {
                coef = std::min(coef, (double)edge.second / (sol[edge.first] - sol[i]));
            }
        }
    }

    double answer = 0;
    for(auto& edge : graph[1]) {
        answer += coef * sol[edge.first];
    }

    return answer;
}

int main() {
    ReadInput();

    BuildEquationSystem();

    Gauss();

    printf("%.8f\n", GetSolution());
	return 0;
}
