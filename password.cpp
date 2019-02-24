/**
  *  Worg
  */
#include <string>
#include <fstream>

std::ifstream fin("password.in"); std::ofstream fout("password.out");

int MinLexicographicalRotation(std::string S) {
    int N = S.size();
    S += S;

    int i = 0, j = 1, k;
    while(j < N) {
        k = 0;
        while(k < N && S[i + k] == S[j + k]) {
            k ++;
        }

        if(S[i + k] <= S[j + k]) {
            j += k + 1;
        } else {
            i += k + 1;
            if(i < j) {
                i = j ++;
            } else {
                j = i + 1;
            }
        }
    }
    return i;
}

int main() {
    std::string S; fin >> S;
    fout << MinLexicographicalRotation(S);
    return 0;
}
