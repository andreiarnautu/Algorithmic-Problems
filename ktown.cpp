/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("ktown.in", "r", stdin); FILE *fout = freopen("ktown.out", "w", stdout);

/*-------- Data --------*/
int N, K;
std::vector<long long > heights, srt;
/*-------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &K);
    heights = srt = std::vector<long long >(N);

    for(auto& h : heights) {
        scanf("%lld", &h);
    }
}

long long GetMinCost() {
    long long answer = 0;

    for(int i = 0; i < N; i++) {
        heights[i] -= 1LL * i * K;
        srt[i] = heights[i];
    }

    std::sort(srt.begin(), srt.end(), [&](long long a, long long b) {
        return a > b;
    });

    for(int i = 0; i < N; i++) {
        answer += srt[0] - heights[i];
    }

    int q = N - 1;
    for(int i = 1; i < N; i++) {
        long long crt = 0, best = 0, nextQ = q;

        for(int j = 0; j <= q; j++) {
            crt += std::abs(srt[i - 1] - heights[j]) - std::abs(srt[i] - heights[j]);

            if(crt > best) {
                best = crt;
                nextQ = j;
            }
        }

        answer -= best; q = nextQ;
    }

    return answer;
}

int main() {
    ReadInput();

    printf("%lld\n", GetMinCost());
	return 0;
}
