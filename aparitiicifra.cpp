/**
  *  Worg
  *
  *  Explicatiile sursei vor fi in romana, insa variabilele si numele functiilor vor fi in engleza,
  *  fiindca asa m-am obisnuit si este mai estetic.
  *
  *  O sa folosesc tipul long long peste tot ca sa fie evitate cazurile particulare unde trebuie avut grija la limite.
  */


#include <fstream>

using namespace std;
ifstream fin("aparitiicifra.in");
ofstream fout("aparitiicifra.out");

long long N, C;

long long countAppearances() {
    /* In general e mai estetic sa lucrati cu o functie care sa va returneze numarul de aparitii in intervalul [1, N].
       E posibil sa mai intalniti problema si in alte forme, iar structura aceasta e mai avantajoasa. */

    /* observam ca daca punem cifra c pe ultima pozitie a numarului, aceasta se repeta o data din 10 in 10 numere
       daca punem cifra c pe penultima pozitie a numarului, se repeta de 10 ori din 100 in 100
       ...

       pentru ultima pozitie, definim o GRUPA ca fiind elementele din intervalul [10k+1, 10k+10]
       pentru penultima pozitie, definim o GRUPA ca fiind elementele din intervalul [100k+1, 100k+100], etc
       */


    long long Answer = 0; /* numarul pe care il returnam, cu alte cuvinte solutia noastra */
    long long Coef = 1; /* puterea lui 10 cu care se inmulteste cifra */
    long long repeatDistance = 10; /* din cate in cate se repeta */
    long long groupCount;

    /* practic in while noi punem cifra c pe fiecare pozitie a numarului, cat timp nu il depaseste ca si valoare
       daca c = 1, atunci la inceput c * Coef = 1, apoi c * Coef = 10, apoi 100 si tot asa */

    while(C * Coef <= N) {
        groupCount = N / repeatDistance; /* numarul de grupe care sunt continute de-a intregul */
        Answer += Coef * groupCount;

        /* mai pot fi ramase numere in ultima grupa, care este incompleta */
        long long Remained = N - repeatDistance * groupCount; /* cate mai raman */
        if(Remained >= C * Coef) {
            /* trebuie sa avem grija sa numaram doar numerele de care avem nevoie */
            if(Remained < Coef * (C + 1)) {
                Answer += Remained - C * Coef + 1;
            } else {
                Answer += Coef;
            }
        }

        Coef *= 10;
        repeatDistance *= 10;
    }

    return Answer;
}

int main() {
    fin >> N >> C;
    fout << countAppearances();
    return 0;
}
