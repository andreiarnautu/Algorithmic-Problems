#include <fstream>

using namespace std;
ifstream fin("palat.in");
ofstream fout("palat.out");

int N, M;
char palat[1001][1001];

struct Casuta {
    int x, y;
};

Casuta coada[1001 * 1001];  // Dimensiunea e egala cu numarul de casute ale palatului, fiindca fiecare poate intra in coada minim o data
int distanta_minima[1001][1001];  // in casuta (i,j) a acestei matrici se gaseste numarul minim de casute pe care il face Ileana ca sa
                                  // ajunga la aceasta casuta.

int dx[4] = {-1, 1, 0,  0};
int dy[4] = { 0, 0, 1, -1};

int main() {
    fin >> N >> M;
    for(int i = 1; i <= N; i++) {
        fin >> (palat[i] + 1);  // Punem +1 ca sa avem linia curenta de pe pozitia 1, ca altfel se citeste de pe pozitia 0
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            distanta_minima[i][j] = 1000000000;  //  initializam distantele minime cu o valoare foarte mare
            if(palat[i][j] == 'I') {  // Daca am gasit-o pe Ileana, ii bagam pozitia in coada si ii actualizam distanta cu 0
                coada[1].x = i;
                coada[1].y = j;
                distanta_minima[i][j] = 0;
            }
        }
    }

    int inceput = 1, sfarsit = 1;  // Pozitiile intre care se afla coada in momentul curent

    while(inceput <= sfarsit) {  // Cat timp mai sunt elemente de verificat in coada
        int x = coada[inceput].x;
        int y = coada[inceput].y;
        inceput ++;

        for(int i = 0; i < 4; i++) {
            // parcurgand vectorii dx si dy, vom obtine in variabilele urm_x si urm_y pe rand coordonatele casutelor invecinate celei curente
            int urm_x = x + dx[i];
            int urm_y = y + dy[i];

            if(1 <= urm_x && urm_x <= N && 1 <= urm_y && urm_y <= M) {  // verificam ca urmatoarea casuta sa fie in interiorul matricii
                if(palat[urm_x][urm_y] != 'Z' && distanta_minima[urm_x][urm_y] > distanta_minima[x][y] + 1) {
                    //  daca am gasit o casuta nevizitata, ii calculam distanta minima si o adugam la coada
                    distanta_minima[urm_x][urm_y] = distanta_minima[x][y] + 1;
                    sfarsit ++;
                    coada[sfarsit].x = urm_x;
                    coada[sfarsit].y = urm_y;
                }
            }
        }
    }

    // odaca calculate distantele minime, urmeaza sa il cautam pe fat frumos (lol)
    Casuta raspuns;
    int distanta_raspuns = 1000000000; // iarasi, initializam distanta minima a unui fat frumos cu ceva foarte mare
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(palat[i][j] == 'F' &&  distanta_raspuns >= distanta_minima[i][j]) {
                distanta_raspuns = distanta_minima[i][j];
                raspuns.x = i;
                raspuns.y = j;
            }
        }
    }

    fout << raspuns.x << " " << raspuns.y << '\n';
    return 0;
}
