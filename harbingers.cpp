/**
  *  Worg
  */
#include <cstdio>
#include <vector>
FILE *fin = freopen("harbingers.in", "r", stdin);
FILE *fout = freopen("harbingers.out", "w", stdout);

const int kMaxN = 1e5 + 1;
const double kMaxInf = 1e18;

/*-------- Structures --------*/
struct Point {
    double x, y;
    Point(const double x, const double y) {
        this->x = x; this->y = y;
    }
};
struct Line {
    double a, b, c;
    Line(const double a, const double b, const double c) {
        this->a = a; this->b = b; this->c = c;
    }
};

Point falsePoint = Point(kMaxInf, kMaxInf);

struct StackElement {
    double left, right; int index;
    StackElement() {}
    StackElement(const double left, const double right, const int index) {
        this->left = left; this->right = right; this->index = index;
    }
};
/*-------- Input data --------*/
int N;
std::vector<std::vector<std::pair<int, int > > > tree;
std::vector<std::pair<int, int > > times;
/*-------- DFS data --------*/
std::vector<Line > lines;
std::vector<StackElement > stack;
std::vector<int > nodeDist;
/*-------- Solution --------*/
std::vector<long long > nodeAnswer;
/*-------- --------*/

void ReadInput() {
    scanf("%d", &N);
    tree.resize(N); times.resize(N); nodeAnswer.resize(N);
    for(int i = 1; i < N; i++) {
        int u, v, d; scanf("%d%d%d", &u, &v, &d);
        u--; v--;
        tree[u].push_back({v, d});
        tree[v].push_back({u, d});
    }
    for(int i = 1; i < N; i++) {
        scanf("%d%d", &times[i].first, &times[i].second);
    }
}

Point GetIntersectionPoint(Line d1, Line d2) {
    long double num = (long double)d1.b * d2.a - (long double)d1.a * d2.b;
    if(num == 0) {
        return falsePoint;
    } else {
        long double x = -(d2.c * d1.b - d1.c * d2.b) / num;
        long double y = (d2.c * d1.a - d1.c * d2.a) / num;
        return Point((double)x, (double)y);
    }
}

void DFS(int node, int father, int end) {
    if(father == 0) {
        nodeAnswer[node] = times[node].first + 1LL * nodeDist[node] * times[node].second;
        lines[node] = Line(nodeDist[node], 1, -nodeAnswer[node]);
        end++; stack[end] = StackElement(-kMaxInf, +kMaxInf, node);
        for(auto& edge : tree[node]) {
            if(edge.first != father) {
                nodeDist[edge.first] = nodeDist[node] + edge.second;
                DFS(edge.first, node, end);
            }
        }
        end--;
    } else {
        int left = 0, right = end, where = end;
        nodeAnswer[node] = times[node].first + 1LL * nodeDist[node] * times[node].second;

        while(left <= right) {
            int mid = (left + right) >> 1;

            if(stack[mid].left <= times[node].second && times[node].second <= stack[mid].right) {
                where = mid; break;
            } else if(times[node].second < stack[mid].left) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        int j = stack[where].index;

        nodeAnswer[node] = std::min(nodeAnswer[node], nodeAnswer[j] - 1LL * nodeDist[j] * times[node].second + 1LL * nodeDist[node] * times[node].second + times[node].first);
        lines[node] = Line(nodeDist[node], 1, -nodeAnswer[node]);

        left = 0; right = end; where = end;
        while(left <= right) {
            int mid = (left + right) >> 1;
            Point P = GetIntersectionPoint(lines[stack[mid].index], lines[node]);

            if(stack[mid].left <= P.x && P.x <= stack[mid].right) {
                where = mid; break;
            } else if(P.x < stack[mid].left) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        Point P = GetIntersectionPoint(lines[stack[where].index], lines[node]);
        StackElement copy_1, copy_2;

        if(where == end) {
            end ++;
        } else {
            end = where + 1;
        }
        copy_1 = stack[end - 1];
        copy_2 = stack[end];
        stack[end] = StackElement(P.x, kMaxInf, node);
        stack[end - 1].right = P.x;

        for(auto& edge : tree[node]) {
            if(edge.first != father) {
                nodeDist[edge.first] = nodeDist[node] + edge.second;
                DFS(edge.first, node, end);
            }
        }
        stack[end] = copy_2;
        stack[end - 1] = copy_1;
    }
}

void WriteOutput() {
    for(int i = 1; i < N; i++) {
        printf("%lld ", nodeAnswer[i]);
    }
    printf("\n");
}

int main() {
    ReadInput();
    lines = std::vector<Line >(N, Line(0, 0, 0));
    stack = std::vector<StackElement > (N, StackElement(0, 0, 0));
    nodeDist.resize(N);
    for(auto edge : tree[0]) {
        nodeDist[edge.first] = edge.second;
        DFS(edge.first, 0, -1);
    }
    WriteOutput();
    return 0;
}
