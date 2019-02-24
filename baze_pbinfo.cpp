/**
  *  Worg
  */
#include <iostream>

using namespace std;

const int MAX_CIFRE = 1 + 9;

/*-------- Date de intrare --------*/
int N, B, C;
/*-------- Date necesare rezolvarii --------*/
int cifre[MAX_CIFRE];
int nr_cifre;
/*-------- --------*/


int main() {
    /* citim datele de intrare */
    cin >> N >> B >> C;

    /* transformam numarul din baza B in baza 10, asemanator programului anterior */
    /* diferenta este ca nu mai avem cifrele intr-un vector. Putem parcurge insa cifrele in aceeasi ordine
        folosindu-ne mereu de ultima cifra a numarului, impartindu-l apoi la 10 */
    int nr_baza_10 = 0;
    int coeficient = 1;

    while(N != 0) {
        int cifra = N % 10;
        N /= 10; /* am folosit ultima cifra, impartim numarul la 10 ca sa o stergem */

        nr_baza_10 += coeficient * cifra;
        coeficient *= B;
    }

    /* avand numarul in baza 10 obtinut, tot ce trebuie sa mai facem este sa il trecem in baza C, folosind metoda resturilor */
    while(nr_baza_10 != 0) {
        nr_cifre ++;
        cifre[nr_cifre] = nr_baza_10 % C;
        nr_baza_10 /= C;
    }

    /* afisam cifrele de la coada la cap */
    for(int i = nr_cifre; i >= 1; i--) {
        cout << cifre[i];
    }
    cout << '\n';

    return 0;
}
