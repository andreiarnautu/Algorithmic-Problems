/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("emptri.in", "r", stdin);
FILE *fout = freopen("emptri.out", "w", stdout);

const int MAX_N = 1 + 1000000;

/*-------- Data --------*/
int N;
int phi[MAX_N];
/*-------- --------*/

void compute_euler_indicator() {
    for(int i = 1; i <= N; i++) {
        phi[i] = i;
    }
    for(int i = 2; i <= N; i += 2) {
        phi[i] >>= 1;
    }

    for(int i = 3; i <= N; i += 2) {
        if(phi[i] == i) {
            for(int j = i; j <= N; j += i) {
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
}

void write_output() {
    long long int solution = 0;
    for(int i = 1; i <= N; i++) {
        solution += phi[i];
    }
    printf("%lld\n", (solution << 1) - 1);
}

int main() {
    scanf("%d", &N);
    compute_euler_indicator();
    write_output();
    return 0;
}
