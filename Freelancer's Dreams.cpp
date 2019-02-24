/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using std::pair;
using std::vector;

//FILE *fin = freopen("main.in", "r", stdin);
//FILE *fout = freopen("main.out", "w", stdout);

/*-------- Structures --------*/
struct Line {
    double a, b, c;
};
/*-------- Input data --------*/
int N;
pair<double, double > P;
vector<pair<double, double > > points;
/*-------- --------*/

void ReadInput() {
    scanf("%d%lf%lf", &N, &P.first, &P.second);
    for(int i = 1; i <= N; i++) {
        double x, y; scanf("%lf%lf", &x, &y);
        points.push_back(std::make_pair(x, y));
    }
}

long double CCW(pair<double, double > p1, pair<double, double > p2, pair<double, double > p3) {
    return (long double)(p2.first - p1.first) * (p3.second - p1.second) -
           (long double)(p3.first - p1.first) * (p2.second - p1.second);
}

vector<pair<double, double > > GetConvexHull(vector<pair<double, double > > points) {
    vector<pair<double, double > > stack;

    std::sort(points.begin(), points.end());

    for(pair<double, double > point : points) {
        while(stack.size() > 1 && CCW(stack[stack.size() - 2], stack[stack.size() - 1], point) >= 0) {
            stack.pop_back();
        }
        stack.push_back(point);
    }

    return stack;
}

Line GetLine(pair<double, double > p1, pair<double, double > p2) {
    Line line;
    line.a = p2.second - p1.second;
    line.b = p1.first - p2.first;
    line.c = p1.second * p2.first - p1.first * p2.second;
    return line;
}

pair<double, double > GetIntersectionPoint(Line l1, Line l2) {
    if(l2.b * l1.a - l1.b * l2.a == 0) {
        return std::make_pair(0, 0);
    } else {
        pair<double, double > answer;
        answer.first =  (l1.b * l2.c - l2.b * l1.c) / (l2.b * l1.a - l1.b * l2.a);
        answer.second = (l2.a * l1.c - l1.a * l2.c) / (l2.b * l1.a - l1.b * l2.a);
        return answer;
    }
}

void WriteOutput() {
    pair<double, double > O = std::make_pair(0, 0);
    Line OP = GetLine(O, P);

    pair<double, double > answer = std::make_pair(0, 0);

    points.push_back(points[0]);
    for(int i = 0; i + 1 < (int)points.size(); i++) {
        Line now = GetLine(points[i], points[i + 1]);
        if(points[i] == points[i + 1]) {
            answer = std::max(answer, points[i]); continue;
        }

        pair<double, double > X = GetIntersectionPoint(OP, now);
        if(std::min(points[i].first, points[i + 1].first) <= X.first && X.first <= std::max(points[i].first, points[i + 1].first) &&
           std::min(points[i].second, points[i + 1].second) <= X.second && X.second <= std::max(points[i].second, points[i + 1].second)) {
                //  Am verificat ca punctul de intersectie apartine segmentului
                answer = std::max(answer, X);
           }
    }

    double SOL = std::max(P.first / answer.first, P.second / answer.second);

    for(int i = 0; i < points.size(); i++) {
        SOL = std::min(SOL, std::max(P.first / points[i].first, P.second / points[i].second));
    }

    printf("%.14f\n", SOL);
}

int main() {
    ReadInput();
    points = GetConvexHull(points);
    WriteOutput();
}
