/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("gold.in", "r", stdin);
FILE *fout = freopen("gold.out", "w", stdout);

const int MAX_N = 1030;

/*************geometrie***************/

struct punct {

    int x;
    int y;
    int index;
    int cant;
};

struct dreapta {

    int a;
    int b;
    int c;
};

dreapta obtineDreapta(const punct &p1, const punct &p2) {

    dreapta d;
    d.a = p2.y - p1.y;
    d.b = p1.x - p2.x;
    d.c = p1.y * p2.x - p1.x * p2.y;
    return d;
}

int semiplan(dreapta d, punct p) {

    return (d.a * p.x + d.b * p.y + d.c);
}

/*************geometrie***************/

int n, p;
punct v[MAX_N], w[MAX_N];

int sum[MAX_N];
int k, ind;

bool comp(punct p1, punct p2) {

    dreapta aux = obtineDreapta(v[ind], p1);
    return (semiplan(aux, p2) >= 0);
}

void readData() {

    scanf("%d%d", &n, &p);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &v[i].cant);
        v[i].index = i;
    }
    for(int i = 1; i <= n; ++i) {
        scanf("%d%d", &v[i].x, &v[i].y);
    }
}

int main() {

    readData();

    int sol = 0, sum1, sum2, sumTotal;

    for(int i = 1; i <= n; ++i) {

        k = 0;
        for(int j = 1; j <= n; ++j)
            if(i != j) {
                w[++k] = v[j];
            }

        ind = i;
        sort(w + 1, w + k + 1, comp);

        sumTotal = 0;
        for(int j = 1; j <= k; ++j) {
            sum[j] = sum[j - 1] + w[j].cant;
            sumTotal += w[j].cant;
        }

        int separator = 2;
        for(int j = 1; j <= k; ++j) {

            dreapta nouaDreapta = obtineDreapta(v[i], w[j]);
            while(semiplan(nouaDreapta, w[separator]) > 0) {
                separator++;
                if(separator == k + 1)
                    separator = 1;
            }

            if(separator <= j) {
                sum1 = sum[k] - sum[j] + sum[separator - 1];
            }
            else {
                sum1 = sum[separator - 1] - sum[j];
            }

            sum2 = sumTotal - sum1 - w[j].cant;
            if(abs(sum1 - sum2) <= p) {
                sol++;
            }

        }
    }

    printf("%d", sol / 2);
    return 0;
}
