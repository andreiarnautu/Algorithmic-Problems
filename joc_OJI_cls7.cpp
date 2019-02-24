#include <fstream>
#include <algorithm>

using namespace std;
ifstream cin("joc.in");
ofstream cout("joc.out");

/*-------- Date de intrare --------*/
int C, N, K;
/*-------- Datele algoritmului --------*/
int m[1 + 100][1 + 100];  /**  Matricea in care simulam mutarile */
int castigate_1, castigate_2;

int mutari[100 * 100 + 1];
int max_marcari;
/*-------- --------*/

int main() {
    cin >> C >> N >> K;

    for(int runda = 1; runda <= K; runda++) {
        /**  Initializare */
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                m[i][j] = 2;
            }
        }

        int cine_incepe;
        if(runda % 2 == 1) {
            cine_incepe = 1;  /**  Teodora */
        } else {
            cine_incepe = 2;  /**  Stefan */
        }

        for(int i = 1; i <= N * N; i++) {  /**  Citim mutarile */
            cin >> mutari[i];
        }

        for(int i = 1; i <= N * N; i++) {
            int a = mutari[i];
            int x = a / N + 1;
            if(a % N == 0) {
                x = a / N;
            }
            int y = a % N;
            if(a % N == 0) {
                y = N;
            }

            /**  Stim ca am marcat casuta (x,y) */
            if(i % 2 == 1) {
                if(cine_incepe == 1) {
                    m[x][y] = 1;
                } else {
                    m[x][y] = 0;
                }
            } else {
                if(cine_incepe == 1) {
                    m[x][y] = 0;
                } else {
                    m[x][y] = 1;
                }
            }

            /**  Verificam linia */
            bool ok = true;  /**  Presupunem ca linia are numai valori identice */
            for(int j = 1; j <= N; j++) {
                if(m[x][j] != m[x][y]) {
                    ok = false; break;
                }
            }

            if(ok == true) {
                if(m[x][y] == 0) {
                    castigate_2++;  /**  Castiga Stefan */
                } else {
                    castigate_1++;  /**  Castiga Teodora */
                }
                max_marcari = max(max_marcari, i);
                break;
            }

            ok = true;
            for(int i = 1; i <= N; i++) {
                if(m[i][y] != m[x][y]) {
                    ok = false; break;
                }
            }

            if(ok == true) {
                if(m[x][y] == 0) {
                    castigate_2++;  /**  Castiga Stefan */
                } else {
                    castigate_1++;  /**  Castiga Teodora */
                }
                max_marcari = max(max_marcari, i);
                break;
            }

            if(x - y == 1) {
                ok = true;
                for(int I = 2, J = 1; I <= N; I++, J++) {
                    if(m[I][J] != m[x][y]) {
                        ok = false; break;
                    }
                }
                if(ok == true) {
                    if(m[x][y] == 0) {
                        castigate_2++;  /**  Castiga Stefan */
                    } else {
                        castigate_1++;  /**  Castiga Teodora */
                    }
                    max_marcari = max(max_marcari, i);
                    break;
                }
            } else if(x - y == 0) {
                ok = true;
                for(int I = 1, J = 1; I <= N; I++, J++) {
                    if(m[I][J] != m[x][y]) {
                        ok = false; break;
                    }
                }
                if(ok == true) {
                    if(m[x][y] == 0) {
                        castigate_2++;  /**  Castiga Stefan */
                    } else {
                        castigate_1++;  /**  Castiga Teodora */
                    }
                    max_marcari = max(max_marcari, i);
                    break;
                }
            } else if(x - y == -1) {
                ok = true;
                for(int I = 1, J = 2; J <= N; I++, J++) {
                    if(m[I][J] != m[x][y]) {
                        ok = false; break;
                    }
                }
                if(ok == true) {
                    if(m[x][y] == 0) {
                        castigate_2++;  /**  Castiga Stefan */
                    } else {
                        castigate_1++;  /**  Castiga Teodora */
                    }
                    max_marcari = max(max_marcari, i);
                    break;
                }
            }

            if(x + y == N) {
                ok = true;
                for(int I = N - 1, J = 1; I >= 1; I--, J++) {
                    if(m[I][J] != m[x][y]) {
                        ok = false; break;
                    }
                }
                if(ok == true) {
                    if(m[x][y] == 0) {
                        castigate_2++;  /**  Castiga Stefan */
                    } else {
                        castigate_1++;  /**  Castiga Teodora */
                    }
                    max_marcari = max(max_marcari, i);
                    break;
                }
            } else if(x + y == N + 1) {
                ok = true;
                for(int I = N, J = 1; I >= 1; I--, J++) {
                    if(m[I][J] != m[x][y]) {
                        ok = false; break;
                    }
                }
                if(ok == true) {
                    if(m[x][y] == 0) {
                        castigate_2++;  /**  Castiga Stefan */
                    } else {
                        castigate_1++;  /**  Castiga Teodora */
                    }
                    max_marcari = max(max_marcari, i);
                    break;
                }
            } else if(x + y == N + 2) {
                ok = true;
                for(int I = N, J = 2; J <= N; I--, J++) {
                    if(m[I][J] != m[x][y]) {
                        ok = false; break;
                    }
                }
                if(ok == true) {
                    if(m[x][y] == 0) {
                        castigate_2++;  /**  Castiga Stefan */
                    } else {
                        castigate_1++;  /**  Castiga Teodora */
                    }
                    max_marcari = max(max_marcari, i);
                    break;
                }
            }
        }
    }

    if(C == 1) {
        cout << castigate_1 << " " << castigate_2 << '\n';
    } else {
        cout << max_marcari;
    }

    return 0;
}
