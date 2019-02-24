/**
  *  Worg
  */
#include <cstdio>
#include <utility>

using std::pair;

FILE *fin = freopen("hof.in", "r", stdin);
FILE *fout = freopen("hof.out", "w", stdout);

const int kMaxParams = 10;

/*-------- Input data --------*/
int N;
/*-------- Algorithm data --------*/
pair<long long, int > params[kMaxParams];
/*-------- --------*/

void InitParams() {
    for(int i = 0; i < kMaxParams; i++) {
        params[i] = std::make_pair(3, 4);
    }
}

inline void Generate(int k);
inline bool Check(int k, int value);

inline void Generate(int k) {
    params[k].first += params[k].second;
    params[k].second += (Check(k + 1, ++params[k].second));
}

inline bool Check(int k, int value) {
    if(value == 1 || value == 3 || value == 7) {
        return true;
    } else if(value <= 7) {
        return false;
    } else {
        while(params[k].first < value) {
            Generate(k);
        }
        return value == params[k].first;
    }
}

int main() {
    InitParams();
    scanf("%d", &N);
    if(N == 1) {
        printf("1\n");
    } else if(N == 2) {
        printf("3\n");
    } else if(N == 3) {
        printf("7\n");
    } else {
        int start = 2;
        if(N >= 50000000) {
            params[0] = std::make_pair(1250329896516380, 50009914);
            start = 50000000;
        }
        for(int i = start + 1; i <= N; i++) {
            Generate(0);
        }
        printf("%lld\n", params[0].first);
    }

    return 0;
}
