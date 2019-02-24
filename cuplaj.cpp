/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("cuplaj.in", "r", stdin);
FILE *fout = freopen("cuplaj.out", "w", stdout);

const int MAX_N = 10000;

vector < int > G[1 + MAX_N];
int left[1 + MAX_N], right[1 + MAX_N];
int n, m, e;
bool checked[1 + MAX_N];

int sol;

void readData() {

    scanf("%d%d%d", &n, &m, &e);
    for(int i = 1; i <= e; ++i) {

        int x, y; scanf("%d%d", &x, &y);
        G[x].push_back(y);
    }
}

/* notatii: (1) - multimea 1, (2) - multimea 2 */

bool pairUp(int node) { /* vrem sa cuplam nodul curent, care este in (1), cu un nod din (2) */

    if(checked[node])
        return 0;
    checked[node] = true;

    for(int nxt : G[node])
        if(!right[nxt]) {   /* daca gasim un vecin din (2) care nu este cuplat, le cuplam si crestem numarul de muchii */

            left[node] = nxt;
            right[nxt] = node;
            sol++;
            return 1;
        }

    /* daca nodul curent are numai vecini cuplati:
            - pentru fiecare vecin din (2) ( care stim ca e cuplat ), notam cu x nodul din (1) cu care face cuplaj
            - daca putem recupla nodul x cu alt nod, o facem si cuplam nodul din (2) cu nodul curent (node) */

    for(int nxt : G[node])
        if(pairUp(right[nxt])) { /* daca nodul decuplat se poate recupla */

            left[node] = nxt;
            right[nxt] = node;
            return 1;
        }

    return 0;
}

int main() {

    readData();

    bool ok;
    do {

        for(int i = 1; i <= n; ++i)
            checked[i] = false;
        ok = false;
        for(int i = 1; i <= n; ++i)
            if(!left[i])
                ok |= pairUp(i);

    }while(ok);

    printf("%d\n", sol);
    for(int i = 1; i <= n; ++i)
        if(left[i])
            printf("%d %d\n", i, left[i]);
    return 0;
}
