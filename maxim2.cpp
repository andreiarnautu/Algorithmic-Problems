/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

FILE *fin = freopen("maxim2.in", "r", stdin);
FILE *fout = freopen("maxim2.out", "w", stdout);

const int kMaxN = 1 + 100000 + 10;
double eps = 1e-12;

/*-------- Input data --------*/
int N;
int v[kMaxN];
int under[kMaxN];
/*-------- Algorithm data --------*/
int zeros;

double solution;

long long cnt[kMaxN];
/*-------- --------*/

void ReadInput() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        scanf("%d", &v[i]);
        if(v[i] != 0) {
            under[v[i]] = 1;
        }
    }
    for(int i = 1; i <= N; i++) {
        under[i] += under[i - 1];
    }
    for(int i = 1; i <= N; i++) {
        under[i] = i - under[i];
    }
}

int CountZeros() {
    int answer = 0;
    for(int i = 1; i <= N; i++) {
        answer += (v[i] == 0);
    }
    return answer;
}

void ZeroZeroTriplets() {  ///  0 0 0
    int k = 0;

    if(zeros < 3) {return;}

    long long aux = 0;
    for(int i = 3; i <= zeros; i++) {
        aux += (i - 2) * (i - 1);
    }

    for(int i = 2; i < N; i++) {
        k += (v[i - 1] == 0 && v[i] == 0 && v[i + 1] == 0);
    }

    //printf("%lld\n", aux * k);
    cnt[zeros - 2] += aux * k;

}

void ZeroConstantTriplets() {  ///  ct 0 0 sau 0 0 ct
    for(int i = 2; i <= N - 1; i++) {
        if(v[i] == 0) {
            if(v[i - 1] == 0 && v[i + 1] != 0) {
                cnt[zeros - 1] += (zeros - 1) * zeros / 2;
                //printf("%d\n", (zeros - 1) * zeros / 2);
                int q = under[v[i + 1]];
                if(q >= 1) {
                    cnt[zeros - 1] -= (q) * (q - 1) / 2;
                    //printf("%d\n", (q - 2) * (q - 1) / 2);
                }
            } else if(v[i - 1] != 0 && v[i + 1] == 0) {
                cnt[zeros - 1] += (zeros - 1) * zeros / 2;
                //printf("%d\n", (zeros - 1) * zeros / 2);
                int q = under[v[i - 1]];
                if(q >= 1) {
                    cnt[zeros - 1] -= (q) * (q - 1) / 2;
                    //printf("%d\n", (q) * (q - 1) / 2);
                }
            }
        }
    }

    //printf("%d\n", cnt[zeros - 1]);
    if(v[1] == 0 && v[2] == 0) {
        cnt[zeros - 1] += (zeros - 1) * zeros / 2;
    }
    if(v[N] == 0 && v[N - 1] == 0) {
        cnt[zeros - 1] += (zeros - 1) * zeros / 2;
    }
}

void ConstantConstantTriplets() {  ///  ct 0 ct
    for(int i = 2; i <= N - 1; i++) {
        if(v[i] == 0 && v[i - 1] != 0 && v[i + 1] != 0) {
            int vmax = std::max(v[i - 1], v[i + 1]);
            cnt[zeros] += under[N] - under[vmax];
        }
    }

    if(v[1] == 0 && v[2] != 0) {
        cnt[zeros] += under[N] - under[v[2]];
    }
    if(v[N] == 0 && v[N - 1] != 0) {
        cnt[zeros] += under[N] - under[v[N - 1]];
    }
}

void ConstantInTheMiddle() {  ///  ct ct ct sau 0 ct ct sau ct ct 0 sau 0 ct 0
    if(v[1] != 0) {
        if(v[2] != 0 && v[1] > v[2]) {
            solution += 1;
        } else if(v[2] == 0) {
            cnt[zeros] += under[v[1]];
            //printf("%d\n", under[v[1]]);
        }
    }

    if(v[N] != 0) {
        if(v[N - 1] != 0 && v[N] > v[N - 1]) {
            solution += 1;
        } else if(v[N - 1] == 0) {
            cnt[zeros] += under[v[N]];
        }
    }

    for(int i = 2; i <= N - 1; i++) {
        if(v[i] != 0) {
            if(v[i - 1] != 0 && v[i + 1] != 0) {   ///  ct ct ct
                if(v[i - 1] < v[i] && v[i] > v[i + 1]) {
                    solution += 1;
                }
            } else if(v[i - 1] == 0 && v[i + 1] == 0) {  /// 0 ct 0
                int q = under[v[i]];
                if(q > 2) {
                    cnt[zeros - 1] += (q - 1) * (q - 2);
                }
            } else if(v[i] > v[i - 1] && v[i] > v[i + 1]) {
                cnt[zeros] += under[v[i]];
            }
        }
    }
}

void GetSolution() {
    ZeroZeroTriplets();
    ZeroConstantTriplets();
    ConstantConstantTriplets();
    ConstantInTheMiddle();

    solution += (double)cnt[zeros] / (double)zeros;


    for(int i = zeros - 1; i >= 1; i--) {
        double crt = cnt[i];
        for(int j = i; j <= zeros && crt > eps; j++) {
            crt /= j;
        }

        if(crt > eps) {
            solution += crt;
        }
    }
}

int main() {
    ReadInput();
    if(N == 1) {
        printf("%.10f\n", 1.0); return 0;
    }
    zeros = CountZeros();
    GetSolution();
    printf("%.13f\n", solution);
    return 0;
}
