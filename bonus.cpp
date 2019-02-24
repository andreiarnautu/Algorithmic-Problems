/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <vector>
#include <climits>
#include <algorithm>

FILE *fin = freopen("bonus.in", "r", stdin); FILE *fout = freopen("bonus.out", "w", stdout);

const int kMaxBase = 1 << 16;
const int kMaxCubeRoot = 2642246;

/*-------- Input data --------*/
int N;
std::vector<std::pair<unsigned long long, int > > queries;
/*-------- Algorithm data --------*/
std::vector<std::pair<unsigned long long, int > > precomputed;

std::vector<unsigned long long > queryAnswers;
/*-------- --------*/

bool Overflow(unsigned long long A, unsigned long long B) {
    return ULLONG_MAX / A < B;
}

void Precompute() {
    for(int i = 2; i <= kMaxBase; i++) {
        std::vector<unsigned long long > powers(1, 1);

        while(!Overflow(powers.back(), i)) {
            powers.push_back(powers.back() * i);
        }

        for(int a = 4; a < (int)powers.size(); a++) {
            for(int b = 0; b < a; b++) {
                if(powers[a] <= ULLONG_MAX - powers[b]) {
                    precomputed.push_back({powers[a] + powers[b], i});
                }
            }
        }
    }

    std::sort(precomputed.begin(), precomputed.end());
}

void ReadInput() {
    scanf("%d", &N); queries.resize(N); queryAnswers.resize(N);

    for(int i = 0; i < N; i++) {
        scanf("%llu", &queries[i].first); queries[i].second = i;
    }
    std::sort(queries.begin(), queries.end());
}

void AnswerQueries() {
    int cursor = 0, cubeRoot = 1;

    for(int i = 0; i < N; i++) {
        while(cursor < (int)precomputed.size() && precomputed[cursor].first < queries[i].first) {
            cursor ++;
        }

        if(cursor < (int)precomputed.size() && queries[i].first == precomputed[cursor].first) {
            queryAnswers[queries[i].second] = precomputed[cursor].second;
        } else {
            while(cubeRoot < kMaxCubeRoot && 1ULL * cubeRoot * cubeRoot * cubeRoot < queries[i].first) {
                cubeRoot ++;
            }
            cubeRoot --;

            unsigned long long x = 1ULL * cubeRoot * cubeRoot * cubeRoot;
            if(x + 1 == queries[i].first || x + cubeRoot == queries[i].first || x + 1ULL * cubeRoot * cubeRoot == queries[i].first) {
                queryAnswers[queries[i].second] = cubeRoot;
            } else {
                unsigned long long squareRoot = sqrt(queries[i].first);

                while(!Overflow(squareRoot, squareRoot) && queries[i].first >= 1ULL * squareRoot * squareRoot) {
                    squareRoot ++;
                }
                squareRoot --;

                x = 1ULL * squareRoot * squareRoot;
                if(x + 1 == queries[i].first || x + squareRoot == queries[i].first) {
                    queryAnswers[queries[i].second] = squareRoot;
                } else {
                    queryAnswers[queries[i].second] = queries[i].first - 1;
                }
            }
        }
    }
}

void WriteOutput() {
    for(auto& answer : queryAnswers) {
        printf("%llu\n", answer);
    }
}

int main() {
    Precompute();

    ReadInput();

    AnswerQueries();

    WriteOutput();
	return 0;
}
