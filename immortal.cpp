/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("immortal.in", "r", stdin);
FILE *fout = freopen("immortal.out", "w", stdout);

const int MAX_N = 1 + 20;

int N, M, I;

int cntLin[MAX_N];
bool a[MAX_N][MAX_N];

struct Mutare {
    int x1, y1, x2, y2;
    Mutare(const int &x1, const int &y1, const int &x2, const int &y2) {
        this->x1 = x1; this->x2 = x2; this->y1 = y1; this->y2 = y2;
    }
};

vector <Mutare> sol;

void readData() {
    scanf("%d%d%d", &N, &M, &I);

    for(int i = 1; i <= I; ++i) {
        int x, y; scanf("%d%d", &x, &y);
        a[x][y] = true;
        cntLin[x]++;
    }
}

bool solved = false;

void back(int rest) {
    if(rest == 1) {
        for(vector <Mutare>::iterator it = sol.begin(); it != sol.end(); ++it) {
            printf("%d %d %d %d\n", it->x1, it->y1, it->x2, it->y2);
        }
        solved = true;
    }
    if(solved) {
        return;
    }

    /* luam fiecare nemuritor la rand si vedem daca are vreo posibilitate de a sari peste alt nemuritor */
    for(int i = N; i > 0; --i) {
        if(cntLin[i]) {
            for(int j = M; j > 0; --j) {
                if(a[i][j]) {
                    /* daca avem un nemuritor pe pozitia (i,j) */
                    if(i > 2 && a[i - 1][j] == true && a[i - 2][j] == false) {
                        a[i - 1][j] = a[i][j] = false;
                        a[i - 2][j] = true;
                        sol.push_back(Mutare(i, j, i - 2, j));
                        cntLin[i]--; cntLin[i - 1]--; cntLin[i - 2]++;
                        back(rest - 1);
                        a[i][j] = a[i - 1][j] = true;
                        a[i - 2][j] = false;
                        sol.pop_back();
                        cntLin[i]++; cntLin[i - 1]++; cntLin[i - 2]--;
                    }

                    if(j > 2 && a[i][j - 1] == true && a[i][j - 2] == false) {
                        a[i][j] = a[i][j - 1] = false;
                        a[i][j - 2] = true;
                        sol.push_back(Mutare(i, j, i, j - 2));
                        cntLin[i]--;
                        back(rest - 1);
                        a[i][j] = a[i][j - 1] = true;
                        a[i][j - 2] = false;
                        sol.pop_back();
                        cntLin[i]++;
                    }

                    if(i + 2 <= N && a[i + 1][j] == true && a[i + 2][j] == false) {
                        a[i][j] = a[i + 1][j] = false;
                        a[i + 2][j] = true;
                        sol.push_back(Mutare(i, j, i + 2, j));
                        cntLin[i]--; cntLin[i + 1]--; cntLin[i + 2]++;
                        back(rest - 1);
                        a[i][j] = a[i + 1][j] = true;
                        a[i + 2][j] = false;
                        sol.pop_back();
                        cntLin[i]++; cntLin[i + 1]++; cntLin[i + 2]--;
                    }

                    if(j + 2 <= M && a[i][j + 1] == true && a[i][j + 2] == false) {
                        a[i][j] = a[i][j + 1] = false;
                        a[i][j + 2] = true;
                        sol.push_back(Mutare(i, j, i, j + 2));
                        cntLin[i]--;
                        back(rest - 1);
                        a[i][j] = a[i][j + 1] = true;
                        a[i][j + 2] = false;
                        sol.pop_back();
                        cntLin[i]++;
                    }
                }
            }
        }
    }
}

int main() {

    readData();
    back(I);

    return 0;
}
