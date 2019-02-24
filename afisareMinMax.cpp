/**
  *  Worg
  */
#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 1 + 1000; /* dimensiunea vectorului */
const int MAX_VAL = 1 + 100000; /* o valoare care sigur e mai mare decat toate elementele vectorului */

/*-------- Input Data --------*/
int N;
int vec[MAX_N];
/*-------- Algorithm data --------*/
int min_value, pos_min;
int max_value, pos_max;
/*-------- --------*/

void read_data() {
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> vec[i];
    }
}

void find_min_and_max() {
    /* vrem sa gasim pozitia pe care se gasesc minimul si maximul */

    min_value = MAX_VAL; /* initializam minimul cu valoarea maxima, pentru a se schimba pe parcursul parcurgerii */

    for(int i = 1; i <= N; i++) {
        if(vec[i] < min_value) {
            /* Daca am dat peste un element mai mic decat valoarea minima curenta, actualizam minimul si pozitia pe care se gaseste */
            min_value = vec[i];
            pos_min = i;
        }

        if(vec[i] > max_value) {
            /* Daca am dat peste un element mai mare decat valoarea maxima curenta, procedam in mod analog ca mai sus */
            max_value = vec[i];
            pos_max = i;
        }
    }
}

void write_output() {
    /* vrem sa afisam secventa dintre pos_min si pos_max */
    /* nu stim care dintre cele 2 pozitii este prima si care este ultima, asa ca vom folosi doua variabile ajutatoare */

    int first = min(pos_min, pos_max);
    int last = max(pos_min, pos_max);

    /* acum tot ce trebuie sa facem e sa afisam elementele dintre first si last */
    for(int i = first; i <= last; i++) {
        cout << vec[i] << " ";
    }
}

int main() {
    read_data();
    find_min_and_max();
    write_output();
    return 0;
}
