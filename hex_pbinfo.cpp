/**
  *  Worg
  */
#include <cstring>
#include <fstream>

using namespace std;
ifstream fin("hex.in");
ofstream fout("hex.out");

const int MAX_LG = 1 + 10000 + 1;

/*-------- Date de intrare --------*/
char sir[MAX_LG];
int lungime;
/*-------- --------*/

int main() {
    fin >> sir + 1;
    lungime = strlen(sir + 1);

    /* fiecarui grup de 4 cifre in baza 2 ii corespunde o singura cifra in scrierea in baza 16 */
    int rest = lungime % 4;

    /* in cazul in care lungimea sirului nu e multiplu de 4, atunci trebuie sa analizam primul grup de cifre separat*/
    if(rest) {
        int baza_16 = 0;
        for(int i = 1; i <= rest; i++) {
            int cifra = sir[i] - '0';
            baza_16 <<= 1;
            baza_16 += cifra;
        }
        if(baza_16 < 10) {
            fout << baza_16;
        } else {
            char c = 'A' + baza_16 - 10;
            fout << c;
        }
    }

    for(int i = rest + 1; i <= lungime; i += 4) {
        /* se poate observa ca luam grupuri de cate 4 cifre */
        int baza_16 = 0;
        for(int j = i; j <= i + 3; j++) {
            int cifra = sir[j] - '0';
            baza_16 <<= 1;
            baza_16 += cifra;
        }

        if(baza_16 < 10) {
            fout << baza_16;
        } else {
            char c = 'A' + baza_16 - 10;
            fout << c;
        }
    }

    return 0;
}
