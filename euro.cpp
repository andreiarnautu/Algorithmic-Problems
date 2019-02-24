/**
  *  Worg
  */
#include <cstdio>
#include <vector>
FILE *fin = freopen("euro.in", "r", stdin);
FILE *fout = freopen("euro.out", "w", stdout);

const int kMaxN = 34567;
const int kMaxSqrt = 190;

/*-------- Structures --------*/
struct Interval {
    int end;
    long long intervalSum, bestValue;
    Interval(int _end, long long _intervalSum, long long _bestValue) {
        this->end = _end; this->intervalSum = _intervalSum; this->bestValue = _bestValue;
    }
};
/*-------- Interval data --------*/
int N, T;
int euro[kMaxN];

int K;
std::vector<Interval > intervals;
/*-------- --------*/

void MakeIntervals() {
    scanf("%d%d", &N, &T);
    for(int i = 0; i < N; i++) {
        scanf("%d", &euro[i]);
    }

    for(long long i = 0, currentSum = 0, totalSum = 0; i < N; i++) {
        currentSum += euro[i]; totalSum += euro[i];
        if(currentSum < 0 || i == N - 1) {
            long long bestValue = totalSum * (i + 1) - T;
            intervals.push_back({(int)i + 1, currentSum, bestValue});
            currentSum = 0;
        }
    }
}

long long RunDP() {
    long long totalSum = intervals[0].intervalSum;

    for(int i = 1; i < (int)intervals.size(); i++) {
        totalSum += intervals[i].intervalSum;
        long long partialSum = intervals[i].intervalSum;

        for(int j = i - 1; j >= 0 && i - j <= kMaxSqrt; j--) {
            if(intervals[i].bestValue < partialSum * intervals[i].end + intervals[j].bestValue - T) {
                intervals[i].bestValue = partialSum * intervals[i].end + intervals[j].bestValue - T;
            }
            partialSum += intervals[j].intervalSum;
        }
    }
    return intervals.back().bestValue;
}

int main() {
    MakeIntervals();
    printf("%lld\n", RunDP());
    return 0;
}
