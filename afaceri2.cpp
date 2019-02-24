/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <algorithm>

FILE *fin = freopen("afaceri2.in", "r", stdin);
FILE *fout = freopen("afaceri2.out", "w", stdout);

const int MAX_N = 1 + 300;
const int TOTAL_AIRPORTS = 4;
const int MAX_INF = 0x3fffffff;

/*-------- Input data --------*/
struct Point {
    double x, y;
    Point() {}
    Point(const double _x, const double _y) { x = _x; y = _y; }
};

int N;
Point airports[MAX_N][TOTAL_AIRPORTS] ;
/*-------- DP --------*/
double dp[MAX_N][MAX_N][TOTAL_AIRPORTS][TOTAL_AIRPORTS];

/*-------- --------*/

void ReadInput() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        for(int j = 0; j < TOTAL_AIRPORTS; j++) {
            scanf("%lf%lf", &airports[i][j].x, &airports[i][j].y);
        }
    }
}

double GetDist(const Point p1, const Point p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                     (p1.y - p2.y) * (p1.y - p2.y));
}

void InitializeDP() {
    //  MAX_INF pentru toate initial
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            for(int x = 0; x < TOTAL_AIRPORTS; x++) {
                for(int y = 0; y < TOTAL_AIRPORTS; y++) {
                    dp[i][j][x][y] = MAX_INF;
                }
            }
        }
    }

    //  Nu are sens sa initializam pentru aeroportul de plecare, adica pentru 1, datorita implementarii
    //  Asa ca vom initializa direct pentru 2

    for(int x = 0; x < TOTAL_AIRPORTS; x++) {
        for(int y = 0; y < TOTAL_AIRPORTS; y++) {
            dp[2][1][x][y] = std::min(dp[2][1][x][y], GetDist(airports[2][x], airports[1][y]));
        }
    }
}

void RunDP() {
    //  Expandam dinamica inainte
    for(int i = 2; i < N; i++) {
        for(int j = 1; j < i; j++) {
            for(int x = 0; x < TOTAL_AIRPORTS; x++) {
                for(int y = 0; y < TOTAL_AIRPORTS; y++) {
                    for(int z = 0; z < TOTAL_AIRPORTS; z++) {
                        //  Expandam primul drum
                        dp[i + 1][i][z][x] = std::min(dp[i + 1][i][z][x],
                                                      dp[i][j][x][y] + GetDist(airports[j][y], airports[i + 1][z]));

                        //  Expandam al doilea drum
                        dp[i + 1][j][z][y] = std::min(dp[i + 1][j][z][y],
                                                      dp[i][j][x][y] + GetDist(airports[i][x], airports[i + 1][z]));
                    }
                }
            }
        }
    }
}

void WriteOutput() {
    double answer = MAX_INF;

    for(int i = 1; i < N; i++) {
        for(int x = 0; x < TOTAL_AIRPORTS; x++) {
            for(int y = 0; y < TOTAL_AIRPORTS; y++) {
                answer = std::min(answer, dp[N][i][x][y] + GetDist(airports[N][x], airports[i][y]));
            }
        }
    }

    printf("%.8f\n", answer);
}

int main() {
    ReadInput();
    InitializeDP();
    RunDP();
    WriteOutput();
    return 0;
}
