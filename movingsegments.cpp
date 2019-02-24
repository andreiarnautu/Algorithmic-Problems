/**
  *  Worg
  */
#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;
//FILE *fin = freopen("movingsegments.in", "r", stdin);
//FILE *fout = freopen("movingsegments.out", "w", stdout);

const int MAX_N = 1 + 100000;
const int MAX_INF = 1 + 1000000000;

int N;
pair<int,int> segm[MAX_N], segm2[MAX_N];

long long sumLeft[MAX_N], sumRight[MAX_N];

bool dupaSecond(const pair<int,int> &A, const pair<int,int> &B) {
    return A.second < B.second;
}

void readData() {
    scanf("%d", &N);
    for(int i = 1; i <= N; ++i) {
        scanf("%d%d", &segm[i].first, &segm[i].second);
        segm2[i].first = segm[i].first;
        segm2[i].second = segm[i].second;
    }
    sort(segm + 1, segm + N + 1);
    sort(segm2 + 1, segm2 + N + 1, dupaSecond);
}

void preProcess() {
    for(int i = 1; i <= N; ++i) {
        sumLeft[i] = sumLeft[i - 1] + 1LL * segm[i].first;
        sumRight[i] = sumRight[i - 1] + 1LL * segm2[i].second;
    }
}

int binarRight(int val) {
    int left = 1, right = N, answer = 0;
    while(left <= right) {
        int mid = (left + right) >> 1;
        if(segm2[mid].second <= val) {
            answer = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return answer;
}

int binarLeft(int val) {
    int left = 1, right = N, answer = N + 1;
    while(left <= right) {
        int mid = (left + right) >> 1;
        if(segm[mid].first >= val) {
            answer = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return answer;
}

long long rightEnds() {
    long long answer = 1LL * MAX_N * MAX_INF;
    for(int i = 1; i < N; ++i) {
        int pos1 = binarRight(segm2[i].second);
        int pos2 = binarLeft(segm2[i].second);

        long long current = 0;
        if(pos1 != 0) {
            current += 1LL * (1LL * pos1 * segm2[i].second - sumRight[pos1]);
        }
        if(pos2 != N + 1) {
            current += 1LL * (sumLeft[N] - sumLeft[pos2 - 1] -1LL *  segm2[i].second * (N - pos2 + 1));
        }
        answer = min(answer, current);
    }
    return answer;
}

long long leftEnds() {
    long long answer = 1LL * MAX_N * MAX_INF;
    for(int i = 2; i <= N; ++i) {
        int pos1 = binarRight(segm[i].first);
        int pos2 = binarLeft(segm[i].first);

        long long current = 0;
        if(pos1 != 0) {
            current += 1LL * pos1 * segm[i].first - sumRight[pos1];
        }
        if(pos2 != N + 1) {
            current += 1LL * (sumLeft[N] - sumLeft[pos2 - 1] - 1LL * segm[i].first * (N - pos2 + 1));
        }
        answer = min(answer, current);
    }
    return answer;
}

int main() {
    readData();
    preProcess();
    if(N == 1) {
        printf("0"); return 0;
    }
    long long answer = 1LL * MAX_N * MAX_INF;
    answer = min(answer, rightEnds());
    answer = min(answer, leftEnds());
    printf("%lld", answer);
    return 0;
}
