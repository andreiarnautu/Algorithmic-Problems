/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using std::pair;
using std::vector;

FILE *fin = freopen("oypara.in", "r", stdin);
FILE *fout = freopen("oypara.out", "w", stdout);

/*-------- Data --------*/
int N;
vector<pair<int, int > > points_up, points_down;
/*-------- --------*/

void ReadInput() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        int x, y1, y2; scanf("%d%d%d", &x, &y1, &y2);
        points_down.push_back(std::make_pair(x, y1));
        points_up.push_back(std::make_pair(x, y2));
    }
}

long long CCW(pair<int, int > p1, pair<int, int > p2, pair<int, int > p3) {
    return 1LL * (p2.first - p1.first) * (p3.second - p1.second) -
           1LL * (p3.first - p1.first) * (p2.second - p1.second);
}

vector<pair<int, int > > GetConvexHull(vector<pair<int, int > > points, bool reversed) {
    vector<pair<int, int > > stack;

    std::sort(points.begin(), points.end());
    if(reversed) {
        std::reverse(points.begin(), points.end());
    }

    for(pair<int, int > point : points) {
        while(stack.size() > 1 && CCW(stack[stack.size() - 2], stack[stack.size() - 1], point) >= 0) {
            stack.pop_back();
        }
        stack.push_back(point);
    }

    return stack;
}

void WriteOutput() {
    int cursor_down = 0, cursor_up = 0;

    for(; cursor_down + 1 < (int)points_down.size(); cursor_down ++) {
        while(cursor_up + 1 < points_up.size() && CCW(points_down[cursor_down], points_up[cursor_up], points_up[cursor_up + 1]) < 0) {
            cursor_up ++;
        }

        if(CCW(points_down[cursor_down], points_down[cursor_down + 1], points_up[cursor_up]) >= 0) {
            printf("%d %d ", points_down[cursor_down].first, points_down[cursor_down].second);
            printf("%d %d\n", points_up[cursor_up].first, points_up[cursor_up].second);
            return ;
        }
    }
}

int main() {
    ReadInput();
    points_down = GetConvexHull(points_down, false);
    points_up = GetConvexHull(points_up, true);
    WriteOutput();

    return 0;
}
