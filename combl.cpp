/**
  *  Worg
  */
#include <set>
#include <cstdio>

using namespace std;
FILE *fin = freopen("combl.in", "r", stdin);
FILE *fout = freopen("combl.out", "w", stdout);

/*-------- Geometry stuff --------*/
struct Point {
    long long x, y;
    Point(const long long _x, const long long _y) {
        x = _x; y = _y;
    }
};

Point origin = Point(0, 0);

struct Line {
    long long a, b, c;
};

Line GetLine(Point p1, Point p2) {
    Line line;
    line.a = p2.y - p1.y;
    line.b = p1.x - p2.x;
    line.c = p1.y * p2.x - p1.x * p2.y;
    return line;
}

long long Indicator(Line line, Point p) {
    return (line.a * p.x + line.b * p.y + line.c);
}

struct comp {
    bool operator() (const Point &p1, const Point &p2) const {
        Line line = GetLine(origin, p1);
        int indicator = Indicator(line, p2);
        if(indicator != 0) {
            return indicator > 0;
        } else {
            if(p1.x != p2.x) {
                return p1.x > p2.x;
            } else {
                return p1.y > p2.y;
            }
        }
    }
};
/*-------- Input data --------*/
int Q;
long long type, x, y;

set<Point, comp> my_set;
/*-------- --------*/

void CheckCompatibility() {
    Point now = origin;
    set<Point, comp>::iterator it;

    /*for(it = my_set.begin(); it != my_set.end(); it++) {
        printf("%lld %lld; ", it->x, it->y);
    }*/

    for(it = my_set.begin(); it != my_set.end(); it++) {
        Line line = GetLine(now, Point(now.x + it->x, now.y + it->y));
        if(Indicator(line, Point(x, y)) < 0) {
            printf("NU\n"); return;
        } else {
            // printf("^");
        }
        now.x += it->x;
        now.y += it->y;
    }


    now = origin;
    it = my_set.end(); it--;
    for(; ; it--) {
        Line line = GetLine(now, Point(now.x + it->x, now.y + it->y));
        if(Indicator(line, Point(x, y)) > 0) {
            printf("NU\n"); return;
        }

        now.x += it->x;
        now.y += it->y;

        if(it == my_set.begin()) {break;}
    }

    printf("DA\n");
}

int main() {
    /*Point p1 = Point(1, 2);
    Point p2 = Point(3, 3);
    Point p3 = Point(2, 2);

    printf("%lld\n", Indicator(GetLine(p1, p2), p3));*/
    for(scanf("%d", &Q); Q > 0; Q--) {
        scanf("%lld%lld%lld", &type, &x, &y);
        // printf("%lld %lld %lld\n", type, x, y);
        if(type == 1) {  // Adaugam punctul dat la multime
            my_set.insert(Point(x, y));
        } else if(type == 2) {  // Stergem punctul din multime
            my_set.erase(Point(x, y));
        } else {  // Verificam daca punctul dat este compatibil
            CheckCompatibility();
        }
    }

    return 0;
}
