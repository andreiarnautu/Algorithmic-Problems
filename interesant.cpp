/**
  *  Worg
  */
#include <ctime>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
ifstream fin("interesant.in");
ofstream fout("interesant.out");

const int MAX_N = 1 + 200;

/*-----------*/
int p, N;               /* generale */
/*-----------*/
string sol, current;    /* cerinta 1 */
/*-----------*/
string sir[MAX_N];      /* cerinta 2 */
vector <int> answers;
/*-----------*/

void compara() {
    int len = (int)sol.size();
    for(int i = 0; i < len; ++i) {
        if(current[i] < sol[i]) {
            sol = current;
            return;
        }
    }
}

void taskOne() {
    for(int i = 1; i <= N; ++i) {
        fin >> current;
        if(current.size() > sol.size()) {
            sol = current;
        }
        else if(current.size() == sol.size()) {
            compara();
        }
    }
    fout << sol << '\n';
}

bool Try(int a, int b) {
    int pos = 0, currentPos = 0;
    int len1 = sir[a].size(), len2 = sir[b].size();

    while(pos < len1 && currentPos < len2) {
        if(sir[a][pos] == sir[b][currentPos]) {
            pos++;
        }
        currentPos++;
    }

    if(pos == len1) {
        return true;
    }
    else {
        return false;
    }
}

void taskTwo() {
    for(int i = 1; i <= N; ++i) {
        fin >> sir[i];
    }

    for(int i = 1; i <= N; ++i) {
        bool found = false;
        for(int j = 1; j <= N; ++j) {
            if(sir[i].size() < sir[j].size()) {
                found = Try(i, j);
                if(found) {
                    break;
                }
            }
        }
        if(!found) {
            answers.push_back(i);
        }
    }

    fout << (int)answers.size() << '\n';
    for(int i = 0; i < (int)answers.size(); ++i) {
        fout << sir[answers[i]] << '\n';
    }
}

int main() {
   /* clock_t startTime = clock(); */


    fin >> p >> N;
    if(p == 1) {
        taskOne();
    }
    else {
        taskTwo();
    }

   /* clock_t finishTime = clock(); */
   /* printf("%.3f", (float)(finishTime - startTime) / CLOCKS_PER_SEC); */
    return 0;
}
