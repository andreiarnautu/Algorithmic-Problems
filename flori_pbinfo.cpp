/**
  *  Code by: Andi Arnautu @Worg
  */
#include <iostream>

using namespace std;

int main() {

    int numarFlori;
    /* citim numarul florilor */
    cin >> numarFlori;

    /* calculam numarul de randuri ( se observa formula ) */
    int numarRanduri = (numarFlori - 1) / 5 + 1;
    cout << numarRanduri << '\n';

    /* ultimul rand este complet daca numarul total de flori este divizibil cu 5 */
    if(numarFlori % 5 == 0)
        cout << "DA\n";
    else
        cout << "NU\n";

    /* parcurgem grupurile de randuri pana cand acestea sunt mai multe sau egale cu numarul de randuri gasit */
    int i, randuriParcurse = 0;
    for(i = 1; i <= 100000; ++i) {      /* conditia i <= 100000 este inutila
                                           se poate la fel de bine pune(for i = 1; ; i++)
                                           daca intelegi de ce este corect si asa, intelegi cum functioneaza for-ul. :D */

        randuriParcurse += i;
        if(randuriParcurse >= numarRanduri)
            break;
    }
    /* daca numarul de grupuri (care se afla in variabila i) este impar, atunci ultimele flori plantate sunt micsunele */
    /* altfel, panselute */
    if(i % 2 == 1)
        cout << "micsunele";
    else
        cout << "panselute";

    return 0;
}
