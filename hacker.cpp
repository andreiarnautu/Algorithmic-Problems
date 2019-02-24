/**
  *  Worg
  */
#include <string>
#include <fstream>

std::ifstream fin("hacker.in");
std::ofstream fout("hacker.out");

const int kModulo = 666013;

int K;

std::string CommonString(std::string a, std::string b) {
    std::string result;
    for(int i = 0; i < (int)a.size(); i++) {
        if(a[i] == '?') {
            result += b[i];
        } else {
            if(b[i] != '?' && a[i] != b[i]) {
                return "";
            } else {
                result += a[i];
            }
        }
    }
    return result;
}

int Count(std::string S) {
    if(S.size() == 1) {
        if(S[0] == '?') {
            return K;
        } else {
            return 1;
        }
    }

    if(S.size() % 2 == 1) {
        if(S[S.size() / 2] == '?') {
            return (K * Count(S.substr(0, S.size() / 2) + S.substr(S.size() / 2 + 1, S.size() / 2))) % kModulo;
        } else {
            return Count(S.substr(0, S.size() / 2) + S.substr(S.size() / 2 + 1, S.size() / 2));
        }
    } else {
        if(S.size() == 0) {
            return 0;
        } else {
            if(S[S.size() / 2 - 1] == '?') {
                return (K * Count(S.substr(0, S.size() / 2 - 1) + S.substr(S.size() / 2, S.size() / 2)) - Count(CommonString(S.substr(0, S.size() / 2), S.substr(S.size() / 2, S.size() / 2))) + kModulo) % kModulo;
            } else {
                return (Count(S.substr(0, S.size() / 2 - 1) + S.substr(S.size() / 2, S.size() / 2)) - Count(CommonString(S.substr(0, S.size() / 2), S.substr(S.size() / 2, S.size() / 2))) + kModulo) % kModulo;
            }
        }
    }
}

int main() {
    int N; std::string S;
    fin >> N >> K >> S;
    fout << Count(S);
    return 0;
}
