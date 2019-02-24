/**
  *  ...stiai ca nu ma dau batut asa usor, nu? :P
  *
  *  Ideea de fill inseamna sa ai o functie recursiva pe care o tot apelezi, pana cand ai terminat de parcurs toate casutele
  *  care sunt zone de uscat.
  *
  *  Si cred ca problema asta chiar e un exemplu bun.
  *  Sursa o sa para mare din cauza explicatiilor, in realitate nu e chiar asa.
  */
#include <fstream>

using namespace std;
ifstream fin("lac.in");
ofstream fout("lac.out");

const int MAX_N = 1 + 1000; /* limita matricei */
const int dx[] = {-1, 1, 0,  0};
const int dy[] = { 0, 0, 1, -1};

/*-------- Date de intrare --------*/
int N, M;
bool matrice[MAX_N][MAX_N];
/*-------- Chestii care tin de fill --------*/
bool verificat[MAX_N][MAX_N]; /** verificat[i][j] == true daca am parcurs deja casuta */
bool estePeninsula;

int numarInsule, numarPeninsule;
/*-------- --------*/

void citesteInput() {
    fin >> N >> M;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            fin >> matrice[i][j];
        }
    }
}

bool inMatrice(int x, int y) {
    return(1 <= x && x <= N && 1 <= y && y <= M);
}

void Fill(int x, int y) {
    verificat[x][y] = true; /* marcam aici ca am verificat casuta, ca sa nu o mai accesam inca o data */

    /** urmeaza sa ne uitam la cei 4 vecini ai casutei.
        Pentru usurinta, am construit vectorii dx[] si dy[] ( uita-te mai sus ).
        Parcurgand vectorii de la 0 la 3, vom obtine in x1 si y1 pe rand coordonatele tuturor celor 4 vecini */

    for(int i = 0; i < 4; i++) {
        int x1 = x + dx[i];
        int y1 = y + dy[i];

        if(inMatrice(x1, y1) && matrice[x1][y1] == 1 && verificat[x1][y1] == false) {
            /* am dat peste alta casuta din zona care nu a fost verificata, deci o parcurgem */
            Fill(x1, y1);
        } else if(!inMatrice(x1, y1)) {
            /* daca vecinul nu e in matrice, inseamna ca zona curenta este lipita de margine, fiind deci peninsula */
            estePeninsula = true;
        }
    }
}

void rezolvaMatricea() {
    /** pentru usurinta, am facut functia inMatrice(x, y), care returneaza true daca casuta accesata e in matrice */

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(matrice[i][j] == 1 && verificat[i][j] == false) {
                /** daca am dat peste o casuta de uscat care nu a fost verificata inca, pornim fill-ul din ea.

                    Acum, e foarte important sa intelegi vizual ce o sa se intample.
                    Odata apelata functia fill(i, j), aceasta va apela recursiv toate casutele de uscat din zona ei si le
                    va marca () ca fiind verificate.

                    De exemplu: cand apelam fill(1, 5), vor fi parcurse toate cele 5 casute din zona de uscat de care apartine
                    si (1, 5). */

                    estePeninsula = false; /* presupunem ca zona nu e lipita de margine */
                    Fill(i, j);

                    if(estePeninsula) {
                        numarPeninsule ++;
                    } else {
                        numarInsule ++;
                    }
            }
        }
    }
}

int main() {
    citesteInput();
    rezolvaMatricea();
    fout << numarInsule << " " << numarPeninsule;
    return 0;
}
