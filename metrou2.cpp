/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("metrou2.in", "r", stdin);
FILE *fout = freopen("metrou2.out", "w", stdout);

const int MAX_N = 1 + 209000 + 1;
const int MAX_K = 1 + 50;

/*-------- Input data --------*/
int N, M;
int profit[MAX_N];
vector< int > graph[MAX_N];
/*-------- Node division --------*/
int degree[MAX_N];
bool has_small_degrees, has_big_degrees;

int big_nodes[MAX_N], count_big_nodes;
int big_index[MAX_N];
/*-------- Chain dp --------*/
int dp[MAX_N][2];
/*-------- Rest of data --------*/
struct Chain {
    int end_1, end_2;
    int dp[2][2];

    Chain() {}
};

Chain chains[MAX_N];
int chain_count;

bool checked[MAX_N];
int chain[MAX_N];

vector< int > small_degree_graph[MAX_N];
int small_degree[MAX_N];

bool no_way[MAX_K][MAX_K];
int Solution;
/*-------- --------*/


void read_input() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; i++) {
        scanf("%d", &profit[i]);
    }
    for(int i = 1; i <= M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        graph[u].push_back(v); graph[v].push_back(u);
        degree[u] ++; degree[v] ++;
    }
}

void divide_nodes() {
    for(int i = 1; i <= N; i++) {
        if(degree[i] < 2) {
            /* am dat peste un nod cu grad mic */
            has_small_degrees = true;
        } else if(degree[i] > 2){
            /* am dat peste un nod cu grad mare */
            has_big_degrees = true;
            big_nodes[count_big_nodes ++] = i;;
            big_index[i] = count_big_nodes;
        }
    }
}

pair<pair<int, int>, pair<int, int> > run_chain_dp(int v[]) {
    dp[0][0] = dp[0][1] = 0;
    dp[1][0] = 0; dp[1][1] = profit[v[1]];

    for(int i = 2; i <= v[0]; i++) {
        dp[i][0] = max(dp[i - 2][0] + profit[v[i]], dp[i - 1][0]);
        dp[i][1] = max(dp[i - 2][1] + profit[v[i]], dp[i - 1][1]);
    }

    return make_pair(make_pair(dp[v[0]][1], dp[v[0] - 1][1]), make_pair(dp[v[0]][0], dp[v[0] - 1][0]));
}

void solve_cycle() {
    /* graful nostru este de fapt un ciclu */

    int node = 1;
    while(!checked[node]) {
        checked[node] = true;
        chain[++chain[0]] = node;

        if(checked[graph[node][0]] == false) {
            node = graph[node][0];
        } else {
            node = graph[node][1];
        }
    }

    /* rulam dinamica pe lant */
    pair<pair<int, int>, pair<int, int> > answer = run_chain_dp(chain);

    /* avem grija sa nu alegem varianta in care sunt alese ambele capete ale lantului */
    Solution = max(answer.first.second, max(answer.second.first, answer.second.second));
}

void solve_chain() {
    /* graful nostru este de fapt un lant */
    int node = 1;
    for(int i = 1; i <= N; i++) {
        if(degree[i] == 1) {
            node = i;
        }
    }

    while(!checked[node]) {
        checked[node] = true;
        chain[++chain[0]] = node;

        if(checked[graph[node][0]] == false) {
            node = graph[node][0];
        } else if(degree[node] > 1){
            node = graph[node][1];
        }
    }


    /* rulam dinamica pe lant */
    pair<pair<int, int> , pair<int, int> > answer = run_chain_dp(chain);

    /* in acest caz putem alege oricare dintre cele 4 stari ale dinamicii */
    Solution = max(max(answer.first.first, answer.first.second), max(answer.second.first, answer.second.second));
}

void make_new_chain(int node) {
    ++ chain_count;
    /* capetele vor fi mereu noduri mari!!! */

    if(small_degree[node] == 0) {
        /* avem un lant format dintr-un singur nod */
        chains[chain_count].end_1 = big_index[graph[node][0]];

        if(degree[node] > 1) {
            chains[chain_count].end_2 = big_index[graph[node][1]];
        } else {
            chains[chain_count].end_2 = count_big_nodes + 1;
        }

        chains[chain_count].dp[0][0] = profit[node];
    } else {
        /* avem un lant legit */

        /* gasim primul capat */
        chains[chain_count].end_1 = count_big_nodes + 1;
        for(int nxt : graph[node]) {
            if(degree[nxt] > 2) {
                chains[chain_count].end_1 = big_index[nxt];
            }
        }

        /* construim partea interioara lantului */
        chain[0] = 0;
        chain[++chain[0]] = node;
        checked[node] = true;

        node = small_degree_graph[node][0];
        chain[++chain[0]] = node;
        checked[node] = true;

        while(small_degree[node] == 2) {
            if(!checked[small_degree_graph[node][0]]) {
                node = small_degree_graph[node][0];
            } else {
                node = small_degree_graph[node][1];
            }

            checked[node] = true;
            chain[++chain[0]] = node;
        }

        /* alegem celalalt capat al lantului */
        chains[chain_count].end_2 = count_big_nodes + 1;
        for(int nxt : graph[node]) {
            if(degree[nxt] > 2) {
                chains[chain_count].end_2 = big_index[nxt];
            }
        }

        /* rulam dinamica pe lant */
        pair<pair<int, int>, pair<int, int> > answer = run_chain_dp(chain);

        chains[chain_count].dp[0][0] = answer.first.first;
        chains[chain_count].dp[0][1] = answer.first.second;
        chains[chain_count].dp[1][0] = answer.second.first;
        chains[chain_count].dp[1][1] = answer.second.second;
    }


}

void solve_problem() {
    divide_nodes();
    if(!has_small_degrees && !has_big_degrees) {
        /* graful e de fapt ciclu */
        solve_cycle();
    } else if(!has_big_degrees) {
        /* graful e de fapt un lant */
        solve_chain();
    } else {
        /* graful nu respecta vreo conditie particulara */

        /* formam graful format din noduri cu grad <= 2 */
        for(int i = 1; i <= N; i++) {
            if(degree[i] <= 2) {
                for(int nxt : graph[i]) {
                    if(degree[nxt] <= 2) {
                        small_degree_graph[i].push_back(nxt);
                        small_degree[i] ++;
                    }
                }
            }
        }

        /* ne ocupam de lanturile formate din aceste noduri */
        for(int i = 1; i <= N; i++) {
            if(degree[i] <= 2 && !checked[i] && small_degree[i] < 2) {
                make_new_chain(i);
            }
        }

        /* verificam perechile de noduri mari care nu pot fi alese simultan */
        for(int i = 0; i < count_big_nodes; i++) {
            int node = big_nodes[i];
            for(int nxt : graph[node]) {
                no_way[i + 1][big_index[nxt]] = true;
            }
        }

        for(int mask = 0; mask < (1 << count_big_nodes); mask++) {
            bool ok = true;
            for(int i = 0; i < count_big_nodes; i++) {
                if(mask & (1 << i)) {
                    for(int j = 0; j < count_big_nodes; j++) {
                        if(mask & (1 << j)) {
                            if(no_way[i + 1][j + 1]) {
                                ok = false;
                            }
                        }
                    }
                }
            }

            if(ok) {
                /* daca avem o configuratie legit */
                int config_value = 0;

                for(int i = 0; i < count_big_nodes; i++) {
                    if(mask & (1 << i)) {
                        config_value += profit[big_nodes[i]];
                    }
                }

                for(int i = 1; i <= chain_count; i++) {
                    int end_1 = chains[i].end_1 - 1;
                    int end_2 = chains[i].end_2 - 1;

                    config_value += chains[i].dp[(mask >> end_1) & 1][(mask >> end_2) & 1];
                }

                Solution = max(Solution, config_value);
            }
        }
    }
}

void write_output() {
    printf("%d\n", Solution);
}

int main() {
    read_input();
    solve_problem();
    write_output();
    return 0;
}
