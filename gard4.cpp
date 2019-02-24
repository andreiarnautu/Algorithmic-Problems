/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <utility>
#include <algorithm>

using std::pair;
using std::priority_queue;

FILE *fin = freopen("gard4.in", "r", stdin);
FILE *fout = freopen("gard4.out", "w", stdout);

const int MAX_N = 1 + 35;
const int MAX_P = 1 + 5;
const int MAX_INF = 2000000000;
const int dx[] = {0,  0,  1, 1, 1, -1, -1, -1};
const int dy[] = {1, -1, -1, 0, 1,  0,  1, -1};

/*-------- Structures --------*/
struct Node {
    int x, y, z;
    int value;
    Node() {}
    Node(const int _x, const int _y, const int _z, const int _value) {x = _x; y = _y; z = _z; value =_value;}

    bool operator <(const Node &other) const {
        return this->value > other.value;
    }
};
/*-------- Input data --------*/
int N, trees;
pair<int, int > tree[MAX_P];
int cost[MAX_N][MAX_N];
/*-------- Algorithm --------*/
priority_queue< Node > heap;

int min_dist[MAX_N][MAX_N][1 << MAX_P];
/*-------- --------*/

void ReadInput() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            int value; scanf("%d", &value);
            if(value == -1) {
                trees ++;
                tree[trees].first = i, tree[trees].second = j;
                cost[i][j] = value;  //  Pentru implementare
            } else {
                cost[i][j] = value;
            }
        }
    }
}

bool CheckPosition(int x, int y) {
    return (1 <= x && x <= N && 1 <= y && y <= N && cost[x][y] != -1);
}

int Dijkstra(int start_x, int start_y) {
    const int MAX_CONFIG = (1 << trees);
    while(!heap.empty()) heap.pop();

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            for(int k = 0; k < MAX_CONFIG; k++) {
                min_dist[i][j][k] = MAX_INF;
            }
        }
    }

    min_dist[start_x][start_y][0] = 0;
    heap.push(Node(start_x, start_y, 0, 0));

    while(!heap.empty()) {
        Node node = heap.top(); heap.pop();
        if(min_dist[node.x][node.y][node.z] == node.value) {
            //printf("Starea (%d %d %d) cu valoarea %d\n", node.x, node.y, node.z, node.value);

            if(node.x == start_x && node.y == start_y && node.z == MAX_CONFIG - 1) {break;}

            for(int i = 0; i < 8; i++) {
                int x = node.x + dx[i];
                int y = node.y + dy[i];
                if(CheckPosition(x, y)) {
                    int z = node.z;
                    for(int j = 1; j <= trees; j++) {
                        if(tree[j].first >= node.x && tree[j].first >= x) {
                            if(tree[j].second == node.y && tree[j].second == y + 1) {
                                z ^= (1 << (j - 1));
                            } else if(tree[j].second == node.y + 1 && tree[j].second == y) {
                                z ^= (1 << (j - 1));
                            }
                        }
                    }

                    if(min_dist[node.x][node.y][node.z] + cost[x][y] < min_dist[x][y][z]) {
                        min_dist[x][y][z] = min_dist[node.x][node.y][node.z] + cost[x][y];
                        heap.push(Node(x, y, z, min_dist[x][y][z]));
                    }
                }
            }
        }
    }

    return min_dist[start_x][start_y][MAX_CONFIG - 1];
}

int GetMinCost() {
    int solution = MAX_INF;
    pair<int, int > left_tree = std::make_pair(0, MAX_N);

    for(int i = 1; i <= trees; i++) {
        if(tree[i].second < left_tree.second) {
            left_tree = tree[i];
        }
    }

    for(int i = 1; i < left_tree.second; i++) {
        //printf("Pornim din (%d %d)\n", left_tree.first, i);
        solution = std::min(solution, Dijkstra(left_tree.first, i));
    }

    return solution;
}

int main() {
    ReadInput();
    printf("%d", GetMinCost());
    return 0;
}
