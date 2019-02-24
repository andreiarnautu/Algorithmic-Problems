/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using std::vector;

FILE *fin = freopen("ab.in", "r", stdin);
FILE *fout = freopen("ab.out", "w", stdout);

const int MAX_N = 1 + 30000;

/*-------- Input data --------*/
int test_count;

int M, N, K;
vector< int > costs;
int B[MAX_N];
/*-------- --------*/

void ReadTestData() {
    scanf("%d%d%d", &M, &N, &K);
    for(int i = 1; i <= K; i++) {
        int cost; scanf("%d", &cost);
        costs.push_back(cost);
    }
    scanf("%d", &B[1]);
    for(int i = 2; i <= M; i++) {
        int diff; scanf("%d", &diff);
        B[i] = B[i - 1] + diff;
    }
}

int GetSolution() {
    int answer, current_sol;
    std::sort(costs.begin(), costs.end());

    //  Avem M acizi si N baze
    //  Initiam punem toti acizii intr-un container si toate bazele in celalalt
    answer = current_sol = std::min(N * costs[0] + M * costs[1], N * costs[1] + M * costs[0]);

    if(K >= 3) {  //  Daca avem si al treilea container, putem reaseza substantele
        int size_1 = N, size_2 = M, size_3 = 0;
        for(int i = 1; i <= M; i++) {
            //  Vrem sa mutam acidul curent in containerul cu baze
            size_1 ++; size_2 --;
            for(int j = B[i - 1] + 1; j <= B[i]; j++) {
                size_1 --; size_3 ++;
            }

            current_sol = std::min(size_1 * costs[0] + size_2 * costs[1] + size_3 * costs[2],
                                   size_2 * costs[0] + size_1 * costs[1] + size_3 * costs[2]);
            current_sol = std::min(current_sol,
                                   std::min(size_1 * costs[0] + size_3 * costs[1] + size_2 * costs[2],
                                            size_3 * costs[0] + size_1 * costs[1] + size_2 * costs[2]));

            current_sol = std::min(current_sol,
                                   std::min(size_2 * costs[0] + size_3 * costs[1] + size_1 * costs[2],
                                            size_3 * costs[0] + size_2 * costs[1] + size_1 * costs[2]));

            answer = std::min(answer, current_sol);
        }
    } else {
        //  Trebuie sa verificam cazul in care primii acizi nu au afinitate fata de nicio baza
        current_sol = N * costs[0] + M * costs[1];
        for(int i = 1; i <= M && B[i] == 0; i++) {
            current_sol -= (costs[1] - costs[0]);
        }
        answer = std::min(answer, current_sol);
    }

    return answer;
}

void ClearData() {
    costs.clear();
}

int main() {
    for(scanf("%d", &test_count); test_count > 0; test_count--) {
        ReadTestData();
        printf("%d\n", GetSolution());
        ClearData();
    }

    return 0;
}
