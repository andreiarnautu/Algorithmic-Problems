/**
  *  Worg
  */
#include <stack>
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("atlas.in", "r", stdin);
FILE *fout = freopen("atlas.out", "w", stdout);

const int MAX_N = 1 + 100000 + 1;
const int MAX_Q = 1 + 100000;
const int MAX_INF = 0x3fffffff;

/*-------- Input data --------*/
int T, N, Q;
long long h[MAX_N];
long long q[MAX_N];
/*-------- Simulare --------*/
stack< pair< long long,int > > Stack;
long long waterNeeded[MAX_N << 1], columnIndex[MAX_N << 1], width[MAX_N << 1], height[MAX_N << 1];
int crtIndex;
/*-------- --------*/

void readInput() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        scanf("%lld", &h[i]);
    }
    scanf("%d", &Q);
    for(int i = 1; i <= Q; i++) {
        scanf("%lld", &q[i]);
    }
}

void simulateWater() {
    h[0] = MAX_INF; h[N + 1] = MAX_INF;
    waterNeeded[0] = 0;
    columnIndex[0] = 0;
    width[0] = 1;
    height[0] = MAX_INF;
    while(!Stack.empty()) {
        Stack.pop();
    }

    long long crtWater = 0;
    Stack.push(make_pair(h[0], 0));

    crtIndex = 0;
    for(int i = 1; i <= N; i++) {
        crtIndex ++;
        waterNeeded[crtIndex] = crtWater;
        columnIndex[crtIndex] = i;
        width[crtIndex] = i - Stack.top().second;
        height[crtIndex] = h[i];

        int lastHeight = h[i];
        Stack.push(make_pair(h[i], i));

        while(h[i + 1] > Stack.top().first) {
            crtWater += 1LL * (i - Stack.top().second) * (Stack.top().first - lastHeight);

            crtIndex ++;
            waterNeeded[crtIndex] = crtWater; /** 1 */
            columnIndex[crtIndex] = i; /** 2 */
            height[crtIndex] = Stack.top().first; /** 3 */

            lastHeight = Stack.top().first; Stack.pop();

            width[crtIndex] = i - Stack.top().second; /** 4 */
        }

        crtWater += 1LL * (i - Stack.top().second) * max(0LL, h[i + 1] - lastHeight);
    }
}

long long cmmdc(long long a, long long b) {
    long long r;
    while(b) {
        r = a % b; a = b; b = r;
    }
    return a;
}

void answerQueries() {
    for(int i = 1; i <= Q; i++) {
        int left = 0, right = crtIndex, Answer = 0;

        while(left <= right) {
            int mid = (left + right) >> 1;

            if(q[i] > waterNeeded[mid]) {
                Answer = mid; left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        long long waterLeft = q[i] + height[Answer] * width[Answer] - waterNeeded[Answer];
        long long gcd = cmmdc(waterLeft, width[Answer]);

        printf("%lld %lld/%lld\n", columnIndex[Answer], waterLeft / gcd, width[Answer] / gcd);
    }
}

int main() {
    int testCount; scanf("%d", &testCount);

    for(; testCount > 0; testCount --) {
        readInput();
        simulateWater();
        answerQueries();
    }

    return 0;
}
