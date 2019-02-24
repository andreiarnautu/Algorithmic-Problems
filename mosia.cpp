/**
  *  Worg
  */
#include <cmath>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;
ifstream fin("mosia.in");
ofstream fout("mosia.out");

const int MAX_N = 1 + 5000;

/*------------geometrie------------*/

bool egale(long double a, long double b) {
    if (a > 0) {
        return (1 - 1e-18) * b <= a && a <= (1 + 1e-18) * b;
    }
    else {
        return (1 - 1e-18) * b >= a && a >= (1 + 1e-18) * b;
    }
}

struct Punct {
    long double x, y, dist;
};

struct Dreapta {
    long double a, b, c;
};

long double dist(Punct p, Punct q) {
    return sqrt((p.x - q.x) * (p.x - q.x) +
                (p.y - q.y) * (p.y - q.y));
}

Dreapta obtineDreapta(Punct p1, Punct p2) {
    Dreapta d;
    d.a = p2.y - p1.y;
    d.b = p1.x - p2.x;
    d.c = p1.y * p2.x - p1.x * p2.y;
    return d;
}

long double semiplan(Dreapta d, Punct p) {
    return (d.a * p.x + d.b * p.y + d.c);
}

/*------------geometrie------------*/

Punct p[MAX_N + 1];
int n;

long double dp[3][MAX_N + 1];
bool usesOne[3][MAX_N + 1];

void readData() {
    fin >> n;
    for(int i = 1; i <= n; ++i) {
        fin >> p[i].x >> p[i].y >> p[i].dist;
    }
    for(int i = 2; i <= n; ++i) {
        if(p[i].y < p[1].y || (p[i].y == p[1].y && p[i].x < p[1].x)) {
            swap(p[1], p[i]);
        }
    }
}

bool comp(const Punct &p1, const Punct &p2) {
    Dreapta d = obtineDreapta(p[1], p1);
    if(!egale(semiplan(d, p2), 0)) {
        return semiplan(d, p2) > 0;
    }
    else {
        return dist(p[1], p1) > dist(p[1], p2);
    }
}

void fix() {
    bool ok = true;
    while(ok) {
        ok = false;
        for(int i = 1; i <= n - 2; ++i) {
            Dreapta d = obtineDreapta(p[i], p[i + 1]);
            if(egale(semiplan(d, p[i + 2]), 0) && dist(p[i], p[i + 1]) > dist(p[i], p[i + 2])) {
                swap(p[i + 1], p[i + 2]);
                ok = true;
            }
        }
        Dreapta d = obtineDreapta(p[n - 1], p[n]);
        if(egale(0, semiplan(d, p[1])) && dist(p[n - 1], p[n]) > dist(p[n - 1], p[1])) {
            ok = true;
            swap(p[n], p[1]);
        }

        d = obtineDreapta(p[n], p[1]);
        if(egale(0, semiplan(d, p[2])) && dist(p[n], p[1]) > dist(p[n], p[2])) {
            ok = true;
            swap(p[1], p[2]);
        }
    }
}

void runDP() {
    p[0] = p[n]; p[n + 1] = p[1];

    dp[1][1] = (long double)p[1].dist * dist(p[0], p[2]) / 2;
    usesOne[1][1] = true;

    bool ok = true;
    for(int i = 2; i < n; ++i) {
        long double current = (long double)p[i].dist * dist(p[i - 1], p[i + 1]) / 2;
        if(current + dp[1][i - 2] > dp[1][i - 1]) {
            dp[1][i] = current + dp[1][i - 2];
            usesOne[1][i] = usesOne[1][i - 2];
            if(i == n - 1) {
                ok = false;
            }
        }
        else {
            dp[1][i] = dp[1][i - 1];
            usesOne[1][i] = usesOne[1][i - 1];
        }
    }

    long double val1 = dp[1][n - 1];
    if(!usesOne[1][n - 1] && ok) {
        val1 += p[n].dist * dist(p[n - 1], p[n + 1]) / 2;
    }

    dp[2][2] = (long double)p[2].dist * dist(p[1], p[3]) / 2;
    usesOne[2][2] = true;
    ok = true;
    for(int i = 3; i <= n; ++i) {
        long double current = (long double)p[i].dist * dist(p[i - 1], p[i + 1]) / 2;
        if(current + dp[2][i - 2] > dp[2][i - 1]) {
            dp[2][i] = current + dp[2][i - 2];
            usesOne[2][i] = usesOne[2][i - 2];
            if(i == n) {
                ok = false;
            }
        }
        else {
            dp[2][i] = dp[2][i - 1];
            usesOne[2][i] = usesOne[2][i - 1];
        }
    }

    long double val2 = dp[2][n];
    if(ok && !usesOne[n]) {
        val2 += p[1].dist * dist(p[0], p[2]) / 2;
    }


    fout << setprecision(10);
    fout << fixed << max(val1, val2);
}

int main() {

    readData();
    sort(p + 2, p + n + 1, comp);
    fix();
    runDP();
    return 0;
}
