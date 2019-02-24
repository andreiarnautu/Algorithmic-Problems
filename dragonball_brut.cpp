/**
  *  Worg
  *  Varianta optima (numere mari)
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("dragonball.in", "r", stdin);
FILE *fout = freopen("dragonball.out", "w", stdout);

const int MAX_N = 1 + 1000;
const int MAX_LEN = 1 + 10000;

struct Huge {
    int size;
    char A[MAX_LEN];
};

long long vec[MAX_N + 1];
long long L;
int n, t;

void readData() {
    scanf("%d%d%lld", &n, &t, &L);
    for(int i = 1; i <= n; ++i) {
        scanf("%lld", &vec[i]);
    }
    vec[++n] = L;
}

bool run(long long D) {

    long long current = 0;
    int left = t, pos = 1;

    while(pos <= n) {
        if(vec[pos] - current <= D) {
            current = vec[pos++];
        }
        else {
            current += D;
            if(--left == -1) {
                return false;
            }
        }
    }

    return true;
}

long long binarySearch() {
    long long left = 1, right = L, answer = L;

    while(left <= right) {
        long long mid = (left + right) >> 1;
        if(run(mid)) {
            answer = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return answer;
}

int main() {

    readData();
    printf("%lld", binarySearch());
    return 0;
}
