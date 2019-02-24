/**
  *  Worg
  */
#include <set>
#include <cstdio>
#include <utility>

using namespace std;
FILE *fin = freopen("joc19.in", "r", stdin);
FILE *fout = freopen("joc19.out", "w", stdout);

const int N = 1 + 6;
const int M = 1 + 8;
const int MAX_MOVES = 1 + 11 + 1;

set < pair<long long, long long> > Set;

int stack[MAX_MOVES][N][M], config[N][M];
int rotation[MAX_MOVES];

int stackSize;

void readData() {
    scanf("%d%d%d%d", &stack[0][3][1], &stack[0][3][2], &stack[0][4][1], &stack[0][4][2]);
    scanf("%d%d%d%d", &stack[0][3][3], &stack[0][3][4], &stack[0][4][3], &stack[0][4][4]);
    scanf("%d%d%d%d", &stack[0][5][1], &stack[0][5][2], &stack[0][6][1], &stack[0][6][2]);
    scanf("%d%d%d%d", &stack[0][1][1], &stack[0][1][2], &stack[0][2][1], &stack[0][2][2]);
    scanf("%d%d%d%d", &stack[0][3][7], &stack[0][3][8], &stack[0][4][7], &stack[0][4][8]);
    scanf("%d%d%d%d", &stack[0][3][5], &stack[0][3][6], &stack[0][4][5], &stack[0][4][6]);

    scanf("%d%d%d%d", &config[3][1], &config[3][2], &config[4][1], &config[4][2]);
    scanf("%d%d%d%d", &config[3][3], &config[3][4], &config[4][3], &config[4][4]);
    scanf("%d%d%d%d", &config[5][1], &config[5][2], &config[6][1], &config[6][2]);
    scanf("%d%d%d%d", &config[1][1], &config[1][2], &config[2][1], &config[2][2]);
    scanf("%d%d%d%d", &config[3][7], &config[3][8], &config[4][7], &config[4][8]);
    scanf("%d%d%d%d", &config[3][5], &config[3][6], &config[4][5], &config[4][6]);
}

bool compara(int index) {
    for(int i = 1; i <= 6; ++i) {
        for(int j = 1; j <= 8; ++j) {
            if(config[i][j] != stack[index][i][j]) {
                return false;
            }
        }
    }
    return true;
}

int minSteps = 100;
int rotationSol[MAX_MOVES];

void rotationOne(int index) {
    rotation[index] = 1;
    stack[index][1][1] = stack[index - 1][1][1];
    stack[index][1][2] = stack[index - 1][1][2];
    for(int i = 4; i <= 7; ++i) {
        stack[index][3][i] = stack[index - 1][3][i];
        stack[index][4][i] = stack[index - 1][4][i];
    }
    stack[index][6][1] = stack[index - 1][6][1];
    stack[index][6][2] = stack[index - 1][6][2];



    stack[index][2][1] = stack[index - 1][4][8];
    stack[index][2][2] = stack[index - 1][3][8];
    stack[index][3][3] = stack[index - 1][2][1];
    stack[index][4][3] = stack[index - 1][2][2];
    stack[index][3][8] = stack[index - 1][5][1];
    stack[index][4][8] = stack[index - 1][5][2];
    stack[index][5][1] = stack[index - 1][4][3];
    stack[index][5][2] = stack[index - 1][3][3];

    stack[index][3][1] = stack[index - 1][4][1];
    stack[index][4][1] = stack[index - 1][4][2];
    stack[index][4][2] = stack[index - 1][3][2];
    stack[index][3][2] = stack[index - 1][3][1];
}

void rotationTwo(int index) {
    rotation[index] = 2;
    stack[index][2][1] = stack[index - 1][2][1];
    stack[index][2][2] = stack[index - 1][2][2];
    for(int i = 1; i <= 3; ++i) {
        stack[index][3][i] = stack[index - 1][3][i];
        stack[index][4][i] = stack[index - 1][4][i];
    }
    stack[index][3][8] = stack[index - 1][3][8];
    stack[index][4][8] = stack[index - 1][4][8];
    stack[index][5][1] = stack[index - 1][5][1];
    stack[index][5][2] = stack[index - 1][5][2];

    stack[index][1][1] = stack[index - 1][4][7];
    stack[index][1][2] = stack[index - 1][3][7];
    stack[index][3][4] = stack[index - 1][1][1];
    stack[index][4][4] = stack[index - 1][1][2];
    stack[index][3][7] = stack[index - 1][6][1];
    stack[index][4][7] = stack[index - 1][6][2];
    stack[index][6][1] = stack[index - 1][4][4];
    stack[index][6][2] = stack[index - 1][3][4];

    stack[index][3][5] = stack[index - 1][3][6];
    stack[index][3][6] = stack[index - 1][4][6];
    stack[index][4][6] = stack[index - 1][4][5];
    stack[index][4][5] = stack[index - 1][3][5];
}

void rotationThree(int index) {
    rotation[index] = 3;
    stack[index][1][2] = stack[index - 1][1][2];
    stack[index][2][2] = stack[index - 1][2][2];
    for(int i = 2; i <= 5; ++i) {
        stack[index][3][i] = stack[index - 1][3][i];
        stack[index][4][i] = stack[index - 1][4][i];
    }
    stack[index][5][2] = stack[index - 1][5][2];
    stack[index][6][2] = stack[index - 1][6][2];

    stack[index][1][1] = stack[index - 1][3][1];
    stack[index][2][1] = stack[index - 1][4][1];
    stack[index][3][1] = stack[index - 1][5][1];
    stack[index][4][1] = stack[index - 1][6][1];
    stack[index][5][1] = stack[index - 1][4][6];
    stack[index][6][1] = stack[index - 1][3][6];
    stack[index][3][6] = stack[index - 1][2][1];
    stack[index][4][6] = stack[index - 1][1][1];

    stack[index][3][7] = stack[index - 1][3][8];
    stack[index][3][8] = stack[index - 1][4][8];
    stack[index][4][8] = stack[index - 1][4][7];
    stack[index][4][7] = stack[index - 1][3][7];
}

void rotationFour(int index) {
    rotation[index] = 4;
    for(int i = 1; i <= 6; ++i) {
        stack[index][i][1] = stack[index - 1][i][1];
    }
    for(int i = 6; i <= 8; ++i) {
        stack[index][3][i] = stack[index - 1][3][i];
        stack[index][4][i] = stack[index - 1][4][i];
    }

    stack[index][1][2] = stack[index - 1][3][2];
    stack[index][2][2] = stack[index - 1][4][2];
    stack[index][3][2] = stack[index - 1][5][2];
    stack[index][4][2] = stack[index - 1][6][2];
    stack[index][5][2] = stack[index - 1][4][5];
    stack[index][6][2] = stack[index - 1][3][5];
    stack[index][3][5] = stack[index - 1][2][2];
    stack[index][4][5] = stack[index - 1][1][2];

    stack[index][3][3] = stack[index - 1][4][3];
    stack[index][3][4] = stack[index - 1][3][3];
    stack[index][4][4] = stack[index - 1][3][4];
    stack[index][4][3] = stack[index - 1][4][4];
}

void back(int steps) {
    if(steps > 11 || steps >= minSteps) {
        return;
    }
    else {
        if(compara(steps)) {
            /* daca am ajuns la configuratia finala, ne oprim */
            if(steps < minSteps) {
                minSteps = steps;
                for(int i = 1; i <= steps; ++i) {
                    rotationSol[i] = rotation[i];
                }
            }
        }
        else {
            rotationOne(steps + 1);
            back(steps + 1);
            rotationThree(steps + 1);
            back(steps + 1);
            rotationTwo(steps + 1);
            back(steps + 1);
            rotationFour(steps + 1);
            back(steps + 1);
        }
    }
}

int main() {
    readData();
    back(0);
    printf("%d\n", minSteps);
    for(int i = 1; i <= minSteps; ++i) {
        printf("%d ", rotationSol[i]);
    }
    return 0;
}
