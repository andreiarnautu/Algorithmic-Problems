/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("grarbore.in", "r", stdin);
FILE *fout = freopen("grarbore.out", "w", stdout);

const int Mod = 666013;
const int MAX_N = 1 + 500;
const int root = 0;

/*-------- Input data --------*/
int test_count;
int vertex_count;
vector< int > graph[MAX_N];
/*-------- DFS data --------*/
bool checked[MAX_N];

int count_trees[MAX_N][MAX_N], count_trees_plus[MAX_N][MAX_N], count_trees_minus[MAX_N][MAX_N];
int knapsack[MAX_N][MAX_N];
/*-------- Solution --------*/
int solution[MAX_N];
/*-------- --------*/

void read_input() {
    scanf("%d", &vertex_count);
    for(int i = 1; i < vertex_count; i++) {
        int u, v; scanf("%d%d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
}

void dfs(int node) {
    int son_count = 0;
    vector< int > sons;

    checked[node] = true;
    for(int son : graph[node]) {
        if(!checked[son]) {
            dfs(son);
            son_count ++;
            sons.push_back(son);
        }
    }

    for(int degree = 0; degree < vertex_count; degree++) {
        for(int i = 0; i <= son_count; i++) {
            knapsack[i][0] = 1;
        }

        for(int i = 1; i <= son_count; i++) {
            int son_id = sons[i - 1];
            for(int j = 1; j <= min(i, degree); j++) {
                knapsack[i][j] = (1LL * knapsack[i - 1][j] +
                                          1LL * knapsack[i - 1][j - 1] * count_trees_minus[son_id][degree]) % Mod;
            }
        }

        count_trees_plus[node][degree] = knapsack[son_count][degree];
        for(int i = 0; i < degree; i++) {
            count_trees_minus[node][degree] += knapsack[son_count][i];
        }

        /* resetam dinamica */
        for(int i = 0; i <= son_count; i++) {
            for(int j = 1; j <= min(i, degree); j++) {
                knapsack[i][j] = 0;
            }
        }

        count_trees_minus[node][degree] %= Mod;
        count_trees[node][degree] = (count_trees_minus[node][degree] + count_trees_plus[node][degree]) % Mod;
    }
}

void get_solution() {
    for(int degree = 1; degree < vertex_count; degree++) {
        for(int node = 0; node < vertex_count; node++) {
            solution[degree] = (solution[degree] + count_trees[node][degree] - count_trees[node][degree - 1] + Mod) % Mod;
        }
        printf("%d ", solution[degree]);
        solution[degree] = 0;
    }
    printf("\n");
}

void reset_data() {
    for(int i = 0; i < vertex_count; i++) {
        checked[i] = false;
        graph[i].clear();
        for(int j = 0; j < vertex_count; j++) {
            count_trees[i][j] = count_trees_minus[i][j] = count_trees_plus[i][j] = 0;
        }
    }
}

int main() {
    for(scanf("%d", &test_count); test_count > 0; test_count--) {
        read_input();
        dfs(root);
        get_solution();
        reset_data();
    }
    return 0;
}
