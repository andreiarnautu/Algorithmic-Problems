/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <vector>
#include <utility>
#include <cstdlib>
#include <algorithm>

using namespace std;
FILE *fin = freopen("elicoptere.in", "r", stdin);
FILE *fout = freopen("elicoptere.out", "w", stdout);

const int MAX_N = 1 + 200;
const int MAX_INF = 0x3fffffff;

/*-------- Input data --------*/
struct Point {
    int x, y;

    Point() {}

    Point(const int _x, const int _y) { x = _x; y = _y;}
};

int type;
int N, K;
Point triangle[MAX_N][3];
/*-------- Checking direct bonds --------*/
struct Line {
    double a, b, c;
};

vector< int > graph[MAX_N];
/*-------- DFS --------*/
struct Edge {
    int x, y;
    double dist;

    Edge(const int _x, const int _y, const double _dist) {
        this->x = _x; this->y = _y; this->dist = _dist;
    }

    bool operator <(const Edge &other) const {
        return this->dist < other.dist;
    }
};
bool checked[MAX_N];
int node_count;
int connected_components;
int pair_number;
/*-------- APM --------*/
vector< Edge > edges;
int father[MAX_N];

double total_dist;
/*-------- --------*/

void read_input() {
    scanf("%d%d%d", &type, &N, &K);
    for(int i = 1; i <= N; i++) {
        for(int j = 0; j < 3; j++) {
            scanf("%d%d", &triangle[i][j].x, &triangle[i][j].y);
        }
    }
}

Line get_line(Point A, Point B) {
    Line answer;

    answer.a = B.y - A.y;
    answer.b = A.x - B.x;
    answer.c = A.y * B.x - A.x * B.y;

    return answer;
}

double with_x_fixed(Point P, Line line) {
    double y = (- line.c - line.a * P.x) / line.b;
    return abs(y - (double)P.y);
}

double with_y_fixed(Point P, Line line) {
    double x = (- line.b * P.y - line.c) / line.a;
    return abs(x - (double)P.x);
}

double get_point_triangle_distance(Point P, int t) {
    double answer = MAX_INF;

    Line line = get_line(triangle[t][0], triangle[t][1]);
    if((triangle[t][0].x <= P.x && P.x <= triangle[t][1].x) || (triangle[t][0].x >= P.x && P.x >= triangle[t][1].x)) {
        answer = min(answer, with_x_fixed(P, line));
    }
    if((triangle[t][0].y <= P.y && P.y <= triangle[t][1].y) || (triangle[t][0].y >= P.y && P.y >= triangle[t][1].y)) {
        answer = min(answer, with_y_fixed(P, line));
    }

    line = get_line(triangle[t][0], triangle[t][2]);
    if((triangle[t][0].x <= P.x && P.x <= triangle[t][2].x) || (triangle[t][0].x >= P.x && P.x >= triangle[t][2].x)) {
        answer = min(answer, with_x_fixed(P, line));
    }
    if((triangle[t][0].y <= P.y && P.y <= triangle[t][2].y) || (triangle[t][0].y >= P.y && P.y >= triangle[t][2].y)) {
        answer = min(answer, with_y_fixed(P, line));
    }

    line = get_line(triangle[t][1], triangle[t][2]);
    if((triangle[t][2].x <= P.x && P.x <= triangle[t][1].x) || (triangle[t][2].x >= P.x && P.x >= triangle[t][1].x)) {
        answer = min(answer, with_x_fixed(P, line));
    }
    if((triangle[t][2].y <= P.y && P.y <= triangle[t][1].y) || (triangle[t][2].y >= P.y && P.y >= triangle[t][1].y)) {
        answer = min(answer, with_y_fixed(P, line));
    }

    return answer;
}

void get_triangle_distance(int u, int v) {
    double min_dist = MAX_INF;

    for(int i = 0 ; i < 3; i++) {
        min_dist = min(min_dist, get_point_triangle_distance(triangle[u][i], v));
    }
    for(int i = 0; i < 3; i++) {
        min_dist = min(min_dist, get_point_triangle_distance(triangle[v][i], u));
    }

    if(min_dist <= (double)K) {
        graph[u].push_back(v);
        graph[v].push_back(u);
        edges.push_back(Edge(u, v, min_dist));

        //printf("%d %d\n", u, v);
    }
}

void get_distances() {
    for(int i = 1; i <= N; i++) {
        for(int j = i + 1; j <= N; j++) {
            get_triangle_distance(i, j);
        }
    }
}

void dfs(int node) {
    node_count ++;
    checked[node] = true;
    for(int nxt : graph[node]) {
        if(!checked[nxt]) {
            dfs(nxt);
        }
    }
}

void check_connected_components() {
    for(int i = 1; i <= N; i++) {
        if(!checked[i]) {
            node_count = 0;
            dfs(i);

            connected_components ++;
            pair_number += node_count * (node_count - 1) / 2;
        }
    }
}

int group(int node) {
    if(node != father[node]) {
        father[node] = group(father[node]);
    }
    return father[node];
}

void unite(int u, int v) {
    u = group(u);
    v = group(v);
    father[u] = v;
}

void run_kruskal() {
    sort(edges.begin(), edges.end());

    for(int i = 1; i <= N; i++) {
        father[i] = i;
    }

    for(Edge edge : edges) {
        if(group(edge.x) != group(edge.y)) {
            total_dist += edge.dist;
            unite(edge.x, edge.y);
        }
    }
}

void write_output() {
    if(type == 1) {
        printf("%d\n", N - connected_components);
    } else if(type == 2) {
        printf("%d\n", pair_number);
    } else {
        printf("%.10f\n", total_dist);
    }
}

int main() {
    read_input();
    get_distances();
    check_connected_components();
    if(type == 3) {
        run_kruskal();
    }
    write_output();
    return 0;
}
