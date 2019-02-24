/**
  *  Worg
  */
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;
ifstream fin("aparitii2.in");
ofstream fout("aparitii2.out");

const int MAX_LEN = 1 + 2000000 + 1;

/*-------- Input data --------*/
string A, B;
/*-------- Z-Algorithm --------*/
string S;
int Z[2][MAX_LEN];
/*-------- Solution --------*/
int Solution[MAX_LEN];
/*-------- --------*/

void readInput() {
    fin >> A >> B;
}

void runZ_Algorithm(int index) {
    int N = S.size();
    int L = -1, R = -1;

    for(int i = 1; i < N; i++) {
        if(i > R) {
            /* suntem in afara oricarui Z-Box */
            if(S[0] == S[i]) {
                L = i; /* avem un now Z-Box */
                R = i - 1; /* il crestem pas cu pas */

                for(int j = 0, k = i; k < N && S[j] == S[k]; j++, k++) {
                    Z[index][i] ++;
                    R ++;
                }
            } else {
                Z[index][i] = 0;
            }
        } else {
            /* ne uitam la Z-Boxul in care ne aflam */
            int before = i - L;
            if(Z[index][before] < R - i + 1) {
                Z[index][i] = Z[index][before];
            } else {
                Z[index][i] = R - i + 1;

                L = i;
                for(int before = Z[index][i]; R + 1 < N && S[R + 1] == S[before]; before++, R++) {
                    Z[index][i] ++;
                }
            }
        }
    }
}

void getSolution() {
    for(int i = B.size(); i + B.size() - 1 < S.size(); i++) {
        Solution[min((int)B.size() / 2, min(Z[0][i], Z[1][S.size() - i]))] ++;
    }

    for(int i = B.size() / 2; i >= 1; i--){
        Solution[i] += Solution[i + 1];
    }
}

void writeOutput() {
    int M = B.size();
    for(int i = 1; i * 2 <= B.size(); i++) {
        fout << Solution[i] << '\n';
    }
}

int main() {
    readInput();
    S = B + A;
    runZ_Algorithm(0);
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    S = B + A;
    runZ_Algorithm(1);
    getSolution();
    writeOutput();
    return 0;
}
