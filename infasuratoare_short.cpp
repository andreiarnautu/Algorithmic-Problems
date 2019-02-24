/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using std::pair;
using std::vector;

FILE *fin = freopen("infasuratoare.in", "r", stdin);
FILE *fout = freopen("infasuratoare.out", "w", stdout);

/*-------- Input data --------*/
int N;
vector<pair<double, double > > points;
/*-------- Convex Hull --------*/
vector<pair<double, double > > stack;
/*-------- --------*/

void ReadInput() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        double x, y; scanf("%lf%lf", &x, &y);
        points.push_back(std::make_pair(x, y));
    }
}

double CCW(pair<double, double > p1, pair<double, double > p2, pair<double, double > p3) {
    return (p2.first - p1.first) * (p3.second - p1.second) -
           (p3.first - p1.first) * (p2.second - p1.second);
}

bool comp(pair<double, double > p1, pair<double, double > p2) {
    return CCW(points[0], p1, p2) < 0;
}

vector<pair<double, double > > GetConvexHull(vector<pair<double, double > > &points) {
    for(int i = 1; i < N; i++) {
        if(points[i] < points[0]) {
            std::swap(points[i], points[0]);
        }
    }
    std::sort(points.begin() + 1, points.end(), comp);

    for(pair<double, double > point : points) {
        while(stack.size() > 1 && CCW(stack[stack.size() - 2], stack[stack.size() - 1], point) > 0) {
            stack.pop_back();
        }
        stack.push_back(point);
    }

    std::reverse(stack.begin(), stack.end());
    return stack;
}

void WriteOutput() {
    printf("%d\n", (int)points.size());
    for(pair<double, double > point : points) {
        printf("%.10f %.10f\n", point.first, point.second);
    }
}

int main() {
    ReadInput();
    points = GetConvexHull(points);
    WriteOutput();
    return 0;
}
