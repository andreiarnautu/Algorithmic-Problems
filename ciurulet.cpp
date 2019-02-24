/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("ciurulet.in", "r", stdin);
FILE *fout = freopen("ciurulet.out", "w", stdout);

const int MAX_N = 1 + 1000000;

int N;

char text[MAX_N], sol[MAX_N];
bool hasDiv[MAX_N];


void readData() {
    scanf("%d", &N);
    scanf("%s", text + 2);
}

void Solve() {
    int answer = 0;

    for(int pos = 2; pos <= N; pos++) {
        if(hasDiv[pos]) {
            sol[pos] = '1';
            answer++;
        } else { /* nu are divizori marcati cu 1 */
            if(text[pos] == '0') {
                sol[pos] = '0';
            } else { /* este marcat cu 1 */
                int i;
                for(i = pos * 2; i <= N; i += pos) {
                    if(text[i] == '1') {
                        break;
                    }
                }
                if(i <= N) {
                    sol[pos] = '0';
                } else { /* nu are multipli marcati cu 1 */
                    sol[pos] = '1';
                    answer++;
                    for(i = pos * 2; i <= N; i += pos) {
                        hasDiv[i] = '1';
                    }
                }
            }
        }
    }

    printf("%d\n%s\n", answer, sol + 2);
}

int main() {
    readData();
    Solve();
    return 0;
}
