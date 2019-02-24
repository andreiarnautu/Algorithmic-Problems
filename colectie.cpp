/**
  *  Worg
  *
  *  Solutia are mai multi pasi, care sunt descrisi in functia main ( in principal ).
  */
#include <cstdio>
#include <vector>
#include <algorithm>

#define limit       1000000

using namespace std;
FILE *fin = freopen("colectie.in", "r", stdin);
FILE *fout = freopen("colectie.out", "w", stdout);

const int MAX_N = 1 + 32,
          INF = 1000000000,
          coef[] = {10003, 7129, 7193, 7207, 7417, 7433, 7489, 7541, 7621, 7759},
          mod = 666013;
struct myStruct {

    long long int value;
    vector < int > p;

    myStruct(const long long int &value, const vector < int > q) {

        this->value = value;
        this->p = q;
    }
};

vector < int > sol;
vector < myStruct > h[mod + 1];

bool found;
int package[MAX_N][15];
int totalDigits[15];
int cnt[15], digits[15], first[15], last[15];
int n, k;
long long int needed;

int power(int base, int exponent) {

    int ret = 1;
    for(; exponent; --exponent)
        ret *= base;
    return ret;
    /** exponentul find mereu <= 8, nu avem nevoie de exponentiere cu complexitate logaritmica */
}

void setDigitArrays() {

    int K = k;

    while(K) {

        digits[++digits[0]] = K% 10;
        K /= 10;
    }
    for(int i = 1; i <= digits[0] / 2; ++i)
        swap(digits[i], digits[digits[0] - i + 1]);

    for(int i = 1; i <= digits[0]; ++i)
        first[i] = first[i - 1] * 10 + digits[i];
    for(int i = digits[0]; i; --i)
        last[i] = last[i + 1] + power(10, digits[0] - i) * digits[i];
}

int checkPosition(int pos, int val) {

    int ret;
    if(digits[pos] < val) {

        ret = (first[pos - 1]) * power(10, digits[0] - pos);
    }
    else if(digits[pos] == val) {

        ret = (first[pos - 1]) * power(10, digits[0] - pos) + last[pos + 1] + 1;
        if(!val)
            ret = (first[pos - 1] - 1) * power(10, digits[0] - pos) + last[pos + 1] + 1;
    }
    else {

        ret = (first[pos - 1] + 1) * power(10, digits[0] - pos);
        if(!val)
            ret = (first[pos - 1]) * power(10, digits[0] - pos);
    }
    return ret;
}

void getCnt() {

    for(int i = 0; i <= 9; ++i) {

        for(int j = 2; j <= digits[0]; ++j) {

            cnt[i] += checkPosition(j, i);
        }
    }
    for(int i = 1; i <= 9; ++i) {

        if(digits[1] > i)
            cnt[i] += power(10, digits[0] - 1);
        else if(digits[1] == i)
            cnt[i] += last[2] + 1;
    }

}

void readPackages() {

    for(int i = 1; i <= n; ++i)
        for(int j = 0; j < 10; ++j)
            scanf("%lld ", &package[i][j]);
}

void hashInsert(int subset) {

    vector < int > usedPackages;
    for(int i = 0; i < 10; ++i)
        totalDigits[i] = 0;

    for(int i = 1; i <= n / 2; ++i)
        if(subset & (1 << (i - 1))) {

            usedPackages.push_back(i);
            for(int j = 0; j < 10; ++j) {

                totalDigits[j] += package[i][j];
                if(totalDigits[j] > cnt[j])
                    return;
            }
        }
    long long int hashVal = 0;
    for(int i = 0; i < 10; ++i)
        hashVal += 1LL * totalDigits[i] * coef[i];

    if(hashVal < needed)
        h[hashVal % mod].push_back(myStruct(hashVal, usedPackages));

    if(hashVal == needed)
        if(!found || sol.size() > usedPackages.size()) {

            found = true;
            sol = usedPackages;
        }
}

void searchHash(int subset) {

    vector < int > usedPackages;
    for(int i = 0; i < 10; ++i)
        totalDigits[i] = 0;
    for(int i = n / 2 + 1; i <= n; ++i)
        if(subset & (1 << (i - n / 2 - 1))) {

            usedPackages.push_back(i);
            for(int j = 0; j < 10; ++j) {

                totalDigits[j] += package[i][j];
                if(totalDigits[j] > cnt[j])
                    return;
            }
        }

    long long int hashVal = 0;
    for(int i = 0; i < 10; ++i)
        hashVal += 1LL * totalDigits[i] * coef[i];
    if(needed == hashVal) {

        if(!found || sol.size() > usedPackages.size()) {

            sol = usedPackages;
            found = true;
        }
    }

    else if(needed > hashVal) {

        long long int level = (needed - hashVal) % mod;
        for(vector < myStruct >::iterator it = h[level].begin(); it != h[level].end(); ++it)
            if(needed - hashVal == it->value && (!found || sol.size() > usedPackages.size() + it->p.size())) {

                found = true;
                sol = it->p;
                for(int i = 0; i < usedPackages.size(); ++i)
                    sol.push_back(usedPackages[i]);
                return;
            }
    }

}

void genSubsets() {

    int subsetMax = (1 << (n / 2));
    for(int subset = 1; subset < subsetMax; ++subset)
        hashInsert(subset);
}

void genSubsets_2() {

    int subsetMax = (1 << (n - n / 2));
    for(int subset = 1; subset < subsetMax; ++subset)
        searchHash(subset);
}

void writeData() {

    if(!found)
        printf("0");
    else {

        printf("1\n%d\n", sol.size());
        for(vector < int >::iterator it = sol.begin(); it != sol.end(); ++it)
            printf("%d ", *it);
    }
}

int main() {

    scanf("%d %d ", &n, &k);
                                /**
                                    Cum incepem rezolvarea problemei? Pare destul de complexa la prima vedere.
                                    Se gaseste usor o rezolvare in O(K + 2^N)...totusi, cu K si N mari, aceasta complexitate iese
                                    extrem de rau din timp. Problema va sfarsi fiind mult mai complexa decat pare.
                                    Mentionez ca testele nu sunt bine grupate, toate tind sa aiba n >= 20, deci sursa trebuie
                                    sa fie foarte bine optimizata ca sa ia punctaj...nenul. De asemenea m-am informat din
                                    articolul de solutii al finalei GInfo pentru a scoate toate punctele.
                                    Cititi intai solutia, inainte de a va uita pe cod. :-)

                                    Voi prezenta acum solutia problemei in pasi:
                                        1) Trebuie sa aflam cate cifre de 0, 1, ..., 9 apar in scrierea numerelor de la 1 la K

                                        2) Este EXTREM de folositor sa construim intai o dinamica in O(K * constanta),
                                           constanta = 10. Putem folosi apoi aceasta dinamica in a verifica daca metoda rapida
                                           de a afla numarul de folosiri a unei cifre este buna.

                                        3) Ideea de a afla numarul de aparitii a unei cifre: vom tine vectorul digits, in care se
                                           afla cifrele lui K ( digits[1] = prima cifra, samd ). digits[0] = numarul de cifre
                                           ale lui K.

                                        4) Vom tine vectorii first si last, cu urmatoarea semnificatie:

                                            - sa consideram K = 134589
                                            - vom avea: first[1] = 1, first[2] = 13, first[3] = 134, first[4] = 1345, samd;
                                                        last[6] = 9, last[5] = 89, last[4] = 589, samd;
                                                             /
                                                            /
                                                           6 este numarul de cifre ale lui K in acest caz
                                            - vectorii digits, first si last se calculeaza in functia setDigitArrays()

                                        5) Bun. Si totusi cum calculam numarul de folosiri ale fiecarei cifre?
                                            - pentru a calcula acest numar, folosim vectorul cnt, unde
                                                    cnt[i] = numarul de folosiri ale cifrei i in scrierea numerelor de la 1 la K
                                                             si i este cifra.
                                            - se calculeaza cnt[i] pe baza urmatoarei formule:
                                                    cnt[i] = suma( numarul de aparitii ale cifrei i pe pozitia j ),
                                                             unde 1 <= j <= numarul de cifre ale lui K.

                                            - mare grija la cnt[0]!! o sa observati ca este o mica diferenta intre formula pentru
                                              cnt[0] si cnt[i], cu i != 0.

                                            - de asemenea mare grija pentru numarul de aparitii ale unei cifre pe prima pozitie!

                                            - in functia getCnt() se afla exact ceea ce am explicat mai sus. Functia se foloseste
                                              de apeluri ale functiei checkPosition(int pos, int val), care returneaza numarul de
                                              aparitii ale cifrei val pe pozitia pos in numerele de la 1 la K.

                                            - functia checkPosition() foloseste...matematica! Cu cateva exemple pe hartie si cu
                                              semnificatia lui first si last, e destul de usor de dedus formula. Mentionez
                                              ca ma mai intalnisem cu acest gen de cerinta si mi-a fost usor sa
                                              reconstruiesc rezolvarea.

                                        6) Acum vine partea a 2-a, si anume: cum alegem pachetele?
                                           Odata aflat numarul de folosiri ale fiecarei cifre, vrem sa gasim un mod rapid de a
                                           alege pachetele. Fiindca fiecare pachet contine 10 marimi, nu se poate face dinamica
                                           pentru a gasi numarul minim de pachete! Ne gandim deci la o rezolvare de genul:
                                           generez toate submultimile posibile de pachete si vad care este cea convenabila( daca
                                           exista ).

                                           -    Pare destul de evidenta solutia intr-o complexitate de O(2^N). Generam fiecare
                                           submultime a multimii de pachete date si verificam pentru fiecare submultime daca
                                           foloseste in total cifrele de care avem nevoie. Totusi, asa cum am zis mai sus...
                                           rezolvarea nu e buna, fiind prea inceata pentru datele problemei.

                                           -    Trebuie optimizata ideea de mai sus, si anume: impartim multimea de pachete in
                                           2 jumatati egale, si anume prima jumatate de pachete(de la 1 la N/2) si a doua
                                           jumatate(de la N/2 + 1 la N).

                                           -    Se genereaza toate submultimile primei jumatati in O( 2 ^ (N/2) ) operatii.
                                                Se genereaza toate submultimle jumatatii secunde in O( 2 ^ (N/2) ) operatii.
                                                Trebuie sa ne gandim la o metoda da a stoca valorile obtinute din submultimile
                                                primei jumatati intr-un mod optim, pentru a fi usor de cautat...hash-uri! (super
                                                folositoare, in general).

                                           -    Astfel, se genereaza toate submultimile primei jumatati. Pentru fiecare submul-
                                                time data, calculam numarul de cifre din fiecare tip folosit. Aceste valori
                                                se afla in vectorul totalDigits. Acum intra in rol hash-urile...pentru un
                                                anumit set de valori al vectorului totalDigits, cum ii pot atribui o valoare
                                                cu sansa extrem de mica de a se repeta ( pentru a fi sansa de 100% de a NU se
                                                repeta, am avea nevoie de hash cu coeficienti ce cresc exponential, de la
                                                ~80.000.000( valoarea maxima a unei valori din totalDigits ) pana la
                                                ~80.000.000 ^ 10, care ar depasi limitele celor 64 de biti ). Evident, se gaseste
                                                un hash cu sansa mai mare ca 99% de reusita care sa fie usor de implementat, si
                                                anume:
                                                    - se aleg 10 numere prime ( vectorul coef )
                                                    - valoarea hashVal se calculeaza altfel:
                                                        hashVal = suma( totalDigits[i] * coef[i] ), 0 <= i <= 9
                                                    - se observa sansa INFIMA de a avea hashVal1 = hashVal2 pentru valori
                                                    ale vectorului totalDigits diferite...si cu 1.000.000 de teste ar merge
                                                    linistit fara coliziuni.
                                                    - pentru a se introduce in hash, se calculeaza etajul pe care va fi
                                                    inserata valoarea, si anume hashVal % mod.
                                                    - impreuna cu valoarea hashVal, in hash mai tinem si pachetele folosite,
                                                    intr-o structura vector
                                                - ce am prezentat eu mai sus, se afla in functia genSubsets()

                                            -   se calculeaza valoarea needed, pe baza vectorului cnt
                                            -   dupa aceea, pentru fiecare submultime a jumatatii secunde, se calculeaza hashVal
                                                si se cauta in hash valoarea needed - hashVal (self-explanatory) -> functia
                                                getSubsets2()

                                        - COMPLEXITATE FINALA : O(2^(N/2)) amortizat. Determinarea vectorului cnt nu schimba
                                        timpul de executie, intrucat foloseste foarte putine operatii, in comparatie cu generarea
                                        submultimilor.

                                        Ca sa inchei, sper ca ati inteles ideea de rezolvare. Codul la prima vedere pare
                                        dezordonat, alambicat as zice, pentru ca ideea de rezolvare da foarte mare libertate
                                        de a implementa ( de la calcularea vectorului cnt, pana la gasirea subsetului bun ).
                                        Altii au rezolvari recursive a vectorului cnt, sau au folosit cautare binara si
                                        sortare in loc de hash-uri...totul tine de maniera proprie. Eu personal sunt fan
                                        hash-uri si nu am ezitat sa le folosesc.

                                        As incadra problema la greutatea unui baraj de seniori, intrucat obtinerea celor 100
                                        de puncte necesita o idee optimizata la maxim si un cod lung si multe locuri unde
                                        pot aparea greseli. Desi usoara la prima vedere, problema ar fi greu de abordat in
                                        conditii de concurs. */


    setDigitArrays();
    getCnt();
    for(int i = 0; i < 10; ++i)
        needed += 1LL * cnt[i] * coef[i];
    readPackages();
    genSubsets();
    genSubsets_2();
    writeData();
    return 0;
}
