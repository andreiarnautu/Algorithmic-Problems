/**
  *  Worg
  */
#include <fstream>

using namespace std;
ifstream fin("lee.in");
ofstream fout("lee.out");

const int MAX_N = 1 + 1000; /* dimensiunea matricii */
const int dx[] = {-1, 1, 0,  0};
const int dy[] = { 0, 0, 1, -1};    /* constantele cu ajutorul carora obtii pozitiile adiacente celei curente */

int matrice[MAX_N][MAX_N];
int coadaX[MAX_N * MAX_N], coadaY[MAX_N * MAX_N]; /* intotdeauna declari aici un vector cu acelasi numar de elemente ca si matricea */
int n, m;

int marcat[MAX_N][MAX_N]; /* marcat[i][j] ==  distanta de la (1,1) la celula (i, j), daca ai ajuns cu Lee-ul in celula (i, j)
                                              0, altfel                                     */

bool inTheMatrix(int x, int y) {    /* iti faci o functie care iti returneaza true daca punctul se afla in matrice */
    return (1 <= x && x <= n && 1 <= y && y <= m);
}

void Lee() {
    int p = 1, u = 1;
    coadaX[u] = 1;
    coadaY[u] = 1;
    marcat[1][1] = 1;

    n = m = 1000; /* le setez aici */

    while(p <= u) {                 /* si uite asa Lee-ul devine mult mai scurt */
        int x = coadaX[p];
        int y = coadaY[p];
        p++;

        for(int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if(inTheMatrix(newX, newY) && !marcat[newX][newY]) {
                marcat[newX][newY] = marcat[x][y] + 1;
                u++;
                coadaX[u] = newX;
                coadaY[u] = newY;
            }
        }
    }

    fout << u << '\n';
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            fout << marcat[i][j] << " ";
        }
        fout << '\n';
    }

    /* BTW, la mine algoritmul de Lee in sine ia 0.03 secunde, iar daca fac afisarea 0.5 secunde, sa nu te sperii */
    /* sorry not sorry */
}

int main() {
    Lee();  /* trec direct la Lee, acolo e ideea. Citirea depinde de problema */
    return 0;
}
