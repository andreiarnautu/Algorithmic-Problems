/**
  *  Worg
  */
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;
ifstream fin("mesaje.in");
ofstream fout("mesaje.out");

const int MAX_LINES = 1 + 128;
const int MAX_WORDS = 1 + 30002;

/*-------------------------*/
string m[MAX_LINES];
int cnt;
/*-------------------------*/
string cuv[2][MAX_WORDS];
int nr[2];
string current;
/*-------------------------*/
bool good[MAX_WORDS];
vector<int> power[MAX_WORDS];
/*-------------------------*/
struct Index {
    int index;
};
Index aux[MAX_WORDS];
/*-------------------------*/

void readData() {
    while(getline(fin, m[cnt])) {
        cnt++;
    }
    cnt--;
}

void getWords(int index, string &str) {
    current.clear();
    int pos = 0;
    for(int i = 0; i < (int)str.size(); ++i) {
        if(str[i] == ' ') {
            cuv[index][pos++] = current;
            current.clear();
        } else {
            current += str[i];
        }
    }
    if(!current.empty()) {
        cuv[index][pos++] = current;
        current.clear();
    }
    nr[index] = pos - 1;
}

void findM() {
    for(int i = cnt; i >= 0; --i) {
        getWords(1, m[i]);
        int limit = min(nr[0], nr[1]);

        bool ok = false;
        for(int j = 0; j <= limit; ++j) {
            if(cuv[0][j] == cuv[1][j]) {
                ok = true;
                break;
            }
        }
        if(ok) {
            for(int j = 0; j <= limit; ++j) {
                if(cuv[0][j] == cuv[1][j]) {
                    good[j] = true;
                }
            }
            break;
        }
    }
}

void getPowers() {
    for(int i = cnt; i >= 0; --i) {
        getWords(1, m[i]);
        int limit = min(nr[0], nr[1]);
        for(int j = 0; j <= limit; ++j) {
            if(good[j] && cuv[0][j] == cuv[1][j]) {
                power[j].push_back(i);
            }
        }
    }
}

int comp(const int& A, const int& B) {
    int limit = min(power[A].size(), power[B].size());
    for(int i = 0; i < limit; ++i) {
        if(power[A][i] != power[B][i]) {
            return power[A][i] > power[B][i];
        }
    }
    if((int)power[A].size() > limit) {
        return 1;
    } else if((int)power[B].size() > limit) {
        return 0;
    } else {
        return -1;
    }
}

bool compIndex(const Index& A, const Index& B) {
    int rez = comp(A.index, B.index);
    if(rez != -1) {
        return rez;
    } else {
        return A.index < B.index;
    }
}

void sortPowers() {
    for(int i = 0; i <= nr[0]; ++i) {
        aux[i].index = i;
    }
    sort(aux, aux + nr[0] + 1, compIndex);

    int SOL = 0;
    for(int i = 0; i <= nr[0]; ++i) {
        if(good[aux[i].index]) {
            SOL++;
        }
    }
    fout << SOL << '\n';
    for(int i = 0; i <= nr[0]; ++i) {
        if(good[aux[i].index]) {
            for(int j = cuv[0][aux[i].index].size() - 1; j >= 0; --j) {
                fout << cuv[0][aux[i].index][j];
            }
            fout << " ";
        }
    }
    fout << '\n';
}

int main() {
    readData();
    getWords(0, m[0]);
    findM();
 /*   getPowers();
    sortPowers();*/
    return 0;
}
