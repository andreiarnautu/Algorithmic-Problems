/**
  *  Worg
  */
#include <ctime>
#include <cstdio>
#include <cstdlib>

using namespace std;
FILE *fin = freopen("aladdin.in", "r", stdin);
FILE *fout = freopen("aladdin.out", "w", stdout);

const int MAX_N = 1 + 1000 + 2;

/*-------- Input data --------*/
int N, M;
int square_count[MAX_N][MAX_N];
/*-------- Solution --------*/
int result[MAX_N][MAX_N];
int partial_count[MAX_N][MAX_N];
/*-------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i < N; i++) {
        for(int j = 1; j < M; j++) {
            scanf("%d", &square_count[i][j]);
        }
    }
}

void CheckIfValid() {
    partial_count[1][1] = result[1][1] + result[1][2] + result[2][1];
    for(int i = 2; i < M; i++) {
        partial_count[1][i] = result[1][i] + result[1][i + 1];
    }
    for(int i = 2; i < N; i++) {
        partial_count[i][1] = result[i][1] + result[i + 1][1];
    }
}

bool TryToComplete() {
    for(int i = N - 1; i >= 1; i--) {
        for(int j = M - 1; j >= 1; j--) {
            partial_count[i][j] = result[i + 1][j] + result[i][j + 1] + result[i + 1][j + 1];
            if(partial_count[i][j] == square_count[i][j]) {
                result[i][j] = 0;
            } else if(partial_count[i][j] == square_count[i][j] - 1) {
                result[i][j] = 1;
            } else {
                return false;
            }
        }
    }

    return true;
}

void DoBacktracking() {
    bool found_solution = false;
    int step_count = 0;
    srand(time(NULL));  // Actualizam seed-ul pentru rand()

    while(!found_solution) {
        step_count ++;

        bool valid = true;
        result[N][M] = rand() % 2;
        for(int i = M - 1; i >= 1 && valid; i--) {
            result[N][i] = rand() % 2;
            if(result[N][i] + result[N][i + 1] > square_count[N - 1][i]) {
                valid = false; break;
            }
        }
        for(int i = N - 1; i >= 1; i--) {
            result[i][M] = rand() % 2;
            if(result[i][M] + result[i + 1][M] > square_count[i][M - 1]) {
                valid = false; break;
            }
        }

        if(result[N - 1][M] + result[N][M - 1] + result[N][M] > square_count[N - 1][M - 1]) {
            valid = false;
        }
        if(valid) {
            //CheckIfValid();
            bool completed = TryToComplete();
            if(completed) {
                return;                                         /** Conditia de oprire a back-ului */
            }
        }
    }
}

void WriteOutput() {
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

int main() {
    ReadInput();
    DoBacktracking();
    WriteOutput();
    return 0;
}
