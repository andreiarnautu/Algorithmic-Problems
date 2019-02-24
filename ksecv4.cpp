/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("ksecv4.in", "r", stdin);
FILE *fout = freopen("ksecv4.out", "w", stdout);

const int MAX_N = 1 + 1000000;
const int MAX_M = 1 + 3000;
const long long INF = 1LL << 60;

long long v[MAX_N];
long long a[MAX_M], b[MAX_M];
int N, K, M;

void readData() {
    scanf("%d%d%d", &N, &K, &M);
    for(int i = 0; i < M; ++i) {
        scanf("%lld", &a[i]);
    }
    for(int i = 0; i < M; ++i) {
        scanf("%lld", &b[i]);
    }
    for(int i = 0; i < N; ++i) {
        v[i] = (a[i % M] ^ b[i / M]);
    }
}

bool go(long long S) {
    S <<= 1;
    int pos = 0, groupCount = 0;
    while(groupCount < K && pos < N) {
        long long valMin = v[pos];
        long long valMax = v[pos];

        while(pos < N) {
            pos++;
            if(v[pos] < valMin) {
                valMin = v[pos];
                if(valMax - valMin > S) {
                    break;
                }
            }
            if(v[pos] > valMax) {
                valMax = v[pos];
                if(valMax - valMin > S) {
                    break;
                }
            }
        }
        groupCount++;
    }

    return (pos == N);
}

void binarySearch() {
    long long left = 0, right = INF, answer = INF;
    while(left <= right) {
        long long mid = (left + right) >> 1;
        if(go(mid)) {
            answer = mid; right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    printf("%lld", answer);
}

int main() {
    readData();
    binarySearch();
    return 0;
}
