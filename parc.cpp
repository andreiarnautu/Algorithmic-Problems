/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("parc.in", "r", stdin);
FILE *fout = freopen("parc.out", "w", stdout);

const int MAX_N = 1 + 2000;
const int MAX_L = 1 + 30000;

int x, y, xA, yA, xB, yB;
int n, m;
pair<int,int> lin[MAX_N], col[MAX_N];
bool swappedX, swappedY;

bool isLine[MAX_L], isCol[MAX_L];

void readData() {
    scanf("%d%d%d%d%d%d", &x, &y, &xA, &yA, &xB, &yB);
    if(xA > xB) {
        swap(xA, xB);
        swappedX = true;
    }
    if(yA > yB) {
        swap(yA, yB);
        swappedY = true;
    }

    scanf("%d", &m);
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d", &lin[i].first, &lin[i].second);
        if(lin[i].first > lin[i].second) {
            swap(lin[i].first, lin[i].second);
        }
    }
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d%d", &col[i].first, &col[i].second);
        if(col[i].first > col[i].second) {
            swap(col[i].first, col[i].second);
        }
    }

    sort(lin + 1, lin + m + 1);
    sort(col + 1, col + n + 1);
}

double calcDist() {
    double answer = 0;
    int gapX = 0, gapY = 0;

    for(int i = 1; i <= m; ++i) {
        if(lin[i].first >= xA && lin[i].first <= xB) {
           // printf("%d ", lin[i].first - gapX);
            isLine[lin[i].first - gapX] = true;
            gapX += lin[i].second - lin[i].first;
        }
    }

    //printf("\n");
    for(int i = 1; i <= n; ++i) {
        if(col[i].first >= yA && col[i].first <= yB) {
            //printf("%d ", col[i].first - gapY);
            isCol[col[i].first - gapY] = true;
            gapY += col[i].second - col[i].first;
        }
    }
    //printf("\n");

    int newX = xB - gapX;
    int newY = yB - gapY;
    xB = newX, yB = newY;

    answer = (double)gapX + (double)gapY + sqrt((double)(newX - xA) * (newX - xA) + (double)(newY - yA) * (newY - yA));
    return answer;
}

int cmmdc(int a, int b) {
    int r;
    while(b) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int pathCount() {
    int answer = 1;

    int k = cmmdc(xB - xA, yB - yA);
    int advanceX = (xB - xA) / k;
    int advanceY = (yB - yA) / k;

    int currentX = xA;
    int currentY = yA;

    if(swappedX) {
        currentX = xB;
        advanceX = -advanceX;
    }
    if(swappedY) {
        currentY = yB;
        advanceY = -advanceY;
    }

    for(int i = 0; i < k; ++i) {
        if(isLine[currentX] && isCol[currentY]) {
            answer <<= 1;
        }
        currentX += advanceX;
        currentY += advanceY;
    }


    return answer;
}

int main() {
    readData();
    printf("%.5f\n", calcDist());
    printf("%d", pathCount());
    return 0;
}
