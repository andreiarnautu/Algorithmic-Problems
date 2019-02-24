/**
  *  Worg
  */
#include <fstream>

using namespace std;
ifstream fin("coduri.in");
ofstream fout("coduri.out");

const int MAX_CIFRE = 1 + 32 + 8; /* numarul maxim de cifre pe care il poate avea un numar citit din input */

/*-------- Date de intrare --------*/
int N, H, D;
/*-------- Date necesare rezolvarii --------*/
int cifre_16[MAX_CIFRE];
int cifre_2[MAX_CIFRE];


int numar_indescifrabile;
/*-------- --------*/

int main() {
    fin >> N >> H >> D;

    /* observam ca D = 4 * H */

    for(int i = 1; i <= N; i++) {
        char c; fin >> c;

        if(c == 'H'){
            /* citim un cod in baza 16 si trebuie sa il transformam in baza 2 */
            for(int j = 1; j <= H; j++) {
                fin >> c;
                int cifra;
                if('A' <= c && c <= 'Z') {
                    cifra = 10 + c - 'A';
                } else {
                    cifra = c - '0';
                }

                /* fiecarei cifre din baza 16 ii corespund 4 cifre in baza 2 */
                for(int k = 3; k >= 0; k--) {
                    if(((1 << k) & cifra) != 0) {
                        fout << 1;
                    } else {
                        fout << 0;
                    }
                }
            }
            fout << '\n';
        } else if(c == 'D') {
            /* citim un cod in baza 2 si trebuie sa il transformam in baza 16 */
            for(int j = 1; j <= H; j++) {
                int in_baza_16 = 0;
                for(int k = 3; k >= 0; k--) {
                    fin >> c;
                    int cifra = c - '0';
                    in_baza_16 += (cifra << k);
                }
                if(in_baza_16 < 10) {
                    fout << in_baza_16;
                } else {
                    char c = 'A' + in_baza_16 - 10;
                    fout << c;
                }
            }
            fout << '\n';
        } else {
            /* citim cifrele din baza 16 si cele din baza 2 */
            for(int j = 1; j <= H; j++) {
                fin >> c;
                if('A' <= c && c <= 'Z') {
                    if(c == 'X') {
                        cifre_16[j] = -1;
                    } else {
                        cifre_16[j] = 10 + c - 'A';
                    }
                } else {
                    cifre_16[j] = c - '0';
                }
            }
            for(int j = 1; j <= D; j++) {
                fin >> c;
                if(c == 'X') {
                    cifre_2[j] = -1;
                } else {
                    cifre_2[j] = c - '0';
                }
            }

            /* noi trebuie sa incercam sa aflam configuratia in baza 16 a numarului dat */
            bool este_indescifrabil = false;
            for(int j = 1; j <= H; j++) {
                if(cifre_16[j] == -1) { /* daca pe pozitia curenta nu se cunoaste valoarea */
                    /* ne vom uita la cifrele din intervalul [4 * j - 3, 4 * j] */
                    bool posibil = true;
                    int baza_16 = 0;
                    for(int k = 4 * j - 3; k <= 4 * j; k++) {
                        if(cifre_2[k] == -1) {
                            posibil = false;
                        } else {
                            baza_16 += (cifre_2[k] << (4 * j - k));
                        }
                    }

                    if(!posibil) {
                        este_indescifrabil = true;
                        /* daca numarul e indescifrabil nu mai are sens sa continuam, deci trecem la randul urmator */
                    } else {
                        cifre_16[j] = baza_16;
                    }
                }
            }

            if(este_indescifrabil) {
                numar_indescifrabile ++;
                fout << 0 << '\n';
            } else {
                for(int j = 1; j <= H; j++) {
                    if(cifre_16[j] < 10) {
                        fout << cifre_16[j];
                    } else {
                        char c = 'A' + cifre_16[j] - 10;
                        fout << c;
                    }
                }
                fout << '\n';
            }
        }
    }

    fout << numar_indescifrabile;
}
