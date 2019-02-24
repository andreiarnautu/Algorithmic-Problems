/**
  *  Worg
  */
#include <deque>
#include <cstdio>
FILE *fin = freopen("caraibe.in", "r", stdin);
FILE *fout = freopen("caraibe.out", "w", stdout);

const int kMaxN = 65000 + 1;
const long long kTotalMoney = 1e10;

/*-------- Data --------*/
int N;
int A[kMaxN];

std::deque<int > queue;
/*-------- --------*/

void ReadInput() {
    scanf("%d", &N);
    for(int i = 1; i <= N - 2; i++) {
        scanf("%d", &A[i]);
    }
}

long long GetMaxMoney() {
    queue.push_back(1);
    for(int i = N - 2; i > 0; i--) {
        int extractCount = N - i - 1 - A[i];
        while(extractCount > 0) {
            if(queue.back() <= extractCount) {
                extractCount -= queue.back(); queue.pop_back();
            } else {
                queue.back() -= extractCount; extractCount = 0;
            }
        }
        queue.push_front(N - i - A[i]);
    }
    long long wastedMoney = 0;
    for(int i = 0; i < (int)queue.size(); i++) {
        wastedMoney += queue[i] * i;
    }
    return kTotalMoney - wastedMoney;
}

int main() {
    ReadInput();
    printf("%lld\n", GetMaxMoney());
    return 0;
}
