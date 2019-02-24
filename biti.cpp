/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;
FILE *fin = freopen("biti.in", "r", stdin);
FILE *fout = freopen("biti.out", "w", stdout);

const int MAX_VAL = (1 << 20);

/*----------------------------*/
int graph[MAX_VAL][2];
int N, Pow;
int unchangedPow;
/*----------------------------*/
int value[MAX_VAL];
bool checked[MAX_VAL], marked[MAX_VAL][2];
char OUTPUT[MAX_VAL + 100];

void constructGraph() {
    const int MAX_BIT = 1 << (Pow - 1);

    for(int i = 0; i < N; i++) {
        int aux = (i - (i & MAX_BIT)) << 1;
        graph[i][0] = aux;
        graph[i][1] = aux + 1;
    }
}

void getArray() {
    int TOTAL_STEPS = 0;

    int crtIndex = 1;
    value[crtIndex] = 0; checked[0] = true;

    while(crtIndex < N) {
        TOTAL_STEPS++;
        int val = value[crtIndex];
        //printf("%d %d\n", crtIndex, val);

        if(!checked[graph[val][0]] && !marked[crtIndex][0]) {
            marked[crtIndex][0] = 1; crtIndex++; value[crtIndex] = graph[val][0]; checked[graph[val][0]] = true;
        } else if(!checked[graph[val][1]] && !marked[crtIndex][1]) {
            marked[crtIndex][1] = 1; crtIndex++; value[crtIndex] = graph[val][1]; checked[graph[val][1]] = true;
        } else {
            checked[value[crtIndex]] = false; marked[crtIndex][0] = marked[crtIndex][1] = false; crtIndex--;
        }
    }
}

void constructSol() {
    int crtPos = 0;
    for(int i = 0; i < Pow; i++) {
        OUTPUT[crtPos++] = '0';
    }
    for(int i = 2; i <= N; i++) {
        OUTPUT[crtPos++] = '0' + (1 & value[i]);
    }
    printf("%s", OUTPUT);
}

int main() {
    scanf("%d", &Pow); unchangedPow = Pow; N = 1 << Pow;
    printf("%d\n", N + Pow - 1);
    constructGraph();
    getArray();
    constructSol();
}
