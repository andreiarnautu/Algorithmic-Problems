/**
  *  Worg
  */
#include <fstream>

using namespace std;
ifstream cin("main.in");
ofstream cout("main.out");

const int MAX_N = 1 + 1000000;

/*-------- --------*/
int N;
/*-------- --------*/
bool checked[MAX_N];
/*-------- --------*/

void ciur() {
    checked[0] = checked[1] = 1;  /* 0 si 1 nu sunt prime */
    for(int i = 4; i <= N; i += 2) {
        checked[i] = 1;
    }

    for(int i = 3; i * i <= N; i += 2) {
        if(checked[i] == 0) { /* i este prim */
            for(int j = i * i; j <= N; j += 2 * i) {
                checked[j] = 1; /* il marcam pe j ca nefiind prim */
            }
        }
    }
}

int main() {
    cin >> N;
    ciur();
    for(int i = 1; i <= N; i++) {
        if(checked[i] == 0) { /* daca numarul e prim, il afisam */
            cout << i << " ";
        }
    }

    return 0;
}
