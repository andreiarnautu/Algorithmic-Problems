/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("infasuratoare.in", "r", stdin);
FILE *fout = freopen("infasuratoare.out", "w", stdout);

const int MAX_N = 120000;

/*****************geometrie******************/

struct Punct {
    double x, y;
};

struct Dreapta {
    double a, b, c;
};

Dreapta obtineDreapta(Punct p1, Punct p2) {

    Dreapta d;
    d.a = p2.y - p1.y;
    d.b = p1.x - p2.x;
    d.c = p1.y * p2.x - p1.x * p2.y;
    return d;
}

double semiplan(Dreapta d, Punct p) {
    return (d.a * p.x + d.b * p.y + d.c);
}

/*****************geometrie******************/

int n;
Punct p[1 + MAX_N];

Punct stiva[1 + MAX_N];
int len;

void readData() {

    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%lf%lf", &p[i].x, &p[i].y);
    }
    for(int i = 2; i <= n; ++i)
        if(p[i].y < p[1].y || (p[i].y == p[1].y && p[i].x < p[1].x)) {
            swap(p[1], p[i]);
        }
}

bool comp(const Punct &p1, const Punct &p2) {
    Dreapta d = obtineDreapta(p[1], p1);
    return semiplan(d, p2) > 0;
}

void obtineInfasuratoare() {

    stiva[1] = p[1];
    stiva[2] = p[2];
    len = 2;

    for(int i = 3; i <= n; ++i) {
        Dreapta d = obtineDreapta(stiva[len - 1], stiva[len]);
        double val = semiplan(d, p[i]);

        if(val == 0) {
            stiva[len] = p[i];
        }
        else {
            if(val < 0) {
                while(val <= 0 && len >= 2) {
                    len--;
                    d = obtineDreapta(stiva[len - 1], stiva[len]);
                    val = semiplan(d, p[i]);
                }
            }
            stiva[++len] = p[i];
        }
    }

    printf("%d\n", len);
    for(int i = len; i >= 1; --i) {
        printf("%.6f %.6f\n", stiva[i].x, stiva[i].y);
    }
}

int main() {

    readData();
    sort(p + 2, p + n + 1, comp);
    obtineInfasuratoare();
    return 0;
}
