/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

FILE *fin = freopen("marsmusic.in", "r", stdin); FILE *fout = freopen("marsmusic.out", "w", stdout);

const int kMaxN = 10000 + 5;
const int kMaxM = 50 + 5;

/*-------- Input data --------*/
int N, M;
int length[kMaxN];
/*-------- Algorithm data --------*/
long long dp[kMaxM][kMaxN];
double prob[kMaxN];
/*-------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &M);

    for(int i = 1; i <= M; i++) {
        scanf("%d", &length[i]);
    }
}

void ComputeDP() {
    dp[0][0] = 1;

    for(int i = 1; i <= M; i++) {  //  Current song

        for(int chosen = M - 1; chosen >= 0; chosen--) {
            for(int time = N - length[i]; time >= 0; time--) {
                dp[chosen + 1][time + length[i]] += dp[chosen][time];
            }
        }
    }
}

double GetSolution() {
    double answer = 0.0;

    for(int i = 1; i <= M; i++) {  //  Treat each song separately
        //  Remove the current object from knapsack
        for(int chosen = 0; chosen < M; chosen ++) {
            for(int time = 0; time <= N - length[i]; time ++) {
                dp[chosen + 1][time + length[i]] -= dp[chosen][time];
            }
        }

        //  Compute prob[]
        for(int endTime = length[i]; endTime <= N; endTime ++) {
            double coef = (double)1 / M;

            for(int songsBefore = 0; songsBefore < M; songsBefore ++) {
                prob[endTime] += coef * dp[songsBefore][endTime - length[i]];
                coef *= (double)(songsBefore + 1) / (M - songsBefore - 1);
            }
        }

        //  Make partial sums
        for(int time = length[i]; time <= N; time ++) {
            prob[time] += prob[time - 1];
        }

        //  Add to solution
        for(int second = 1; second <= N; second ++) {  //  How many times the songs overlap during this second
            double x = prob[std::min(N, second + length[i] - 1)] - prob[second - 1];

            answer += x * x;
        }

        //  Readd this song to knapsack
        for(int chosen = M - 1; chosen >= 0; chosen --) {
            for(int time = N - length[i]; time >= 0; time--) {
                dp[chosen + 1][time + length[i]] += dp[chosen][time];
            }
        }

        for(int i = 0; i <= N; i++) {
            prob[i] = 0.0;
        }
    }

    return answer;
}

int main() {
    ReadInput();

    ComputeDP();

    printf("%.9f\n", GetSolution());
	return 0;
}
