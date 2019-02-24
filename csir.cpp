/**
  *  Worg
  */
#include <string>
#include <fstream>
#include <algorithm>

std::ifstream fin("csir.in"); std::ofstream fout("csir.out");

bool AdjustString(std::string &S) {
    int countA = 0;
    for(auto& ch : S) {
        countA += (ch == 'A');
    }
    if(countA == 0 || countA == (int)S.size()) {
        return true;  //  Good string
    } else {
        if(countA <= (int)S.size() / 2) {
            for(auto &ch : S) {
                ch = (ch == 'A') ? 'B' : 'A';
            }
        }
        return false;
    }
}

bool GetNewString(std::string &S) {
    int length = S.size();
    for(int i = 1; i <= length; i++) {
        if(S[i % length] == 'B' && S[i - 1] == 'B') {
            return false;  //  We can't have 2 adjacent B's
        }
    }

    int i = 0;
    int minLength = 1e5, maxLength = 0;

    if(S.back() == 'A') {
        while(i < length && S[i] == 'A') {
            i ++;
        }
    }

    while(i < length) {
        if(S[i] == 'A') {
            int j = i, count = 0;
            while(S[j] == 'A') {
                count ++;
                j = (j == length - 1) ? 0 : j + 1;
                i = (i == length - 1) ? i : i + 1;
            }
            minLength = std::min(minLength, count); maxLength = std::max(maxLength, count);
        }
        i ++;  //  Skip the next B
    }

    if(maxLength - minLength > 1) {
        return false;
    } else {
        std::string newS;

        i = 0;
        if(S.back() == 'A') {
            while(i < length && S[i] == 'A') {
                i ++;
            }
        }

        while(i < length) {
            if(S[i] == 'A') {
                int j = i, count = 0;
                while(S[j] == 'A') {
                    count ++;
                    j = (j == length - 1) ? 0 : j + 1;
                    i = (i == length - 1) ? i : i + 1;
                }
                if(count == minLength) {
                    newS += 'A';
                } else {
                    newS += 'B';
                }
            }
            i ++;  //  Skip the next B
        }

        S = newS; return true;
    }
}

bool SolveString(std::string S) {
    bool verdict = AdjustString(S);

    if(verdict == true) {
        return true;
    } else {
        verdict = GetNewString(S);
        if(verdict == false) {
            return false;
        } else {
            return SolveString(S);
        }
    }
}

bool SolveNewTest() {
    std::string S; fin >> S;
    return SolveString(S);
}

int main() {
    int testCount; fin >> testCount;
    for(int i = 1; i <= testCount; i++) {
        fout << SolveNewTest() << '\n';
    }
    return 0;
}
