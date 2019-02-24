/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("cerc3.in", "r", stdin);
FILE *fout = freopen("cerc3.out", "w", stdout);

const int MAX_N = 1 + 2000;
const int MAX_INF = 0x3fffffff;

/*-------- Input data --------*/
struct Point {
    double x, y, r;
    double slope;
    double first, last;

    Point() {}

    bool operator <(const Point &other) const {
        if(this->slope != other.slope) {
            return this->slope < other.slope;
        } else {
            return this->last < other.last;
        }
    }
};
int N;
Point Points[MAX_N];
/*-------- Solution --------*/
int M;
/*-------- --------*/

void readInput() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        scanf("%lf%lf%lf", &Points[i].x, &Points[i].y, &Points[i].r);
    }
}

double getDist(Point p) {
    return sqrt(p.x * p.x + p.y * p.y);
}

void processData() {
    /** pante */
    for(int i = 1; i <= N; i++) {
        if(Points[i].y == 0) {
            Points[i].slope = MAX_INF;
        } else {
            Points[i].slope = Points[i].x / Points[i].y;
        }
    }

    /** distante */
    for(int i = 1; i <= N; i++) {
        double dist = getDist(Points[i]);
        Points[i].first = dist - Points[i].r;
        Points[i].last = dist + Points[i].r;
    }
}

void getAnswers() {
    sort(Points + 1, Points + N + 1);

    int maxCircles = -1, howMany = -1;
    int crtCircles = 1, lastIndex = 1;

    M = 1;
    for(int i = 2; i <= N; i++) {
        if(Points[i].slope != Points[i - 1].slope) {
            /* am trecut la alta dreapta */
            M ++;
            if(crtCircles > maxCircles) {
                maxCircles = crtCircles;
                howMany = 1;
            } else if(crtCircles == maxCircles) {
                howMany ++;
            }
            crtCircles = 1;
            lastIndex = i;
        } else {
            if(Points[i].first > Points[lastIndex].last) {
                crtCircles ++;
                lastIndex = i;
            }
        }
    }

    if(crtCircles > maxCircles) {
        maxCircles = crtCircles;
        howMany = 1;
    } else if(crtCircles == maxCircles) {
        howMany ++;
    }

    printf("%d %d %d\n", M, maxCircles, howMany);
}

int main() {
    readInput();
    processData();
    getAnswers();
    return 0;
}
