/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
FILE *fin = freopen("banuti.in", "r", stdin);
FILE *fout = freopen("banuti.out", "w", stdout);

const int kMaxN = 50000;
const int kMaxInf = 1e9;
const int kMaxLimit = 5000;

/*-------- Input data --------*/
int N;
int money[kMaxN];
/*-------- Algorithm data --------*/
int firstOccurence[kMaxLimit], edgeCost[kMaxLimit];
bool inQueue[kMaxLimit];
std::queue<int > queue;
/*-------- --------*/

int ReadInput() {
    int minValue = kMaxInf;
    scanf("%d", &N);
    for(int i = 0; i < N; i++) {
        scanf("%d", &money[i]);
        minValue = std::min(minValue, money[i]);
    }
    return minValue;
}

int SolveProblem(int minValue) {
    for(int i = 0; i < minValue; i++) {
        firstOccurence[i] = edgeCost[i] = kMaxInf;
    }
    for(int i = 0; i < N; i++) {
        firstOccurence[money[i] % minValue] = edgeCost[money[i] % minValue] = std::min(firstOccurence[money[i] % minValue], money[i]);
    }
    for(int i = 0; i < minValue; i++) {
        if(firstOccurence[i] != kMaxInf) {
            queue.push(i);
            inQueue[i] = true;
        }
    }
    while(!queue.empty()) {
        auto node = queue.front(); queue.pop(); inQueue[node] = false;

        for(int i = 0, j = node; i < minValue; i++, j = (j == minValue - 1) ? 0 : (j + 1)) {
            if(edgeCost[i] != kMaxInf && firstOccurence[node] + edgeCost[i] < firstOccurence[j]) {
                firstOccurence[j] = firstOccurence[node] + edgeCost[i];
                if(!inQueue[j]) {
                    queue.push(j); inQueue[j] = true;
                }
            }
        }
    }

    int solution = -1;
    for(int i = 0; i < minValue; i++) {
        solution = std::max(solution, firstOccurence[i]);
    }
    return (solution == kMaxInf) ? -1 : (solution - minValue);
}

int main() {
    printf("%d\n", SolveProblem(ReadInput()));
    return 0;
}
