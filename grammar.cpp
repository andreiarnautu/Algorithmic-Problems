/**
  *  Worg
  */
#include <set>
#include <string>
#include <bitset>
#include <ctime>
#include <iostream>
#include <cstdlib>

using namespace std;
//ifstream cin("main.in");
//ofstream cout("main.out");

const int MAX_N = 1 + 1020;
const int Sigma = 100;

/*-------- Input data --------*/
string String, Rule;
/*-------- Solving characters for each sequence --------*/
set< char > One[Sigma];
set< char > Two[Sigma][Sigma];
set< char > Options[MAX_N][MAX_N];
bitset< MAX_N > checked[MAX_N];

time_t startingTime;
/*-------- --------*/

void readInput() {
    startingTime = clock();

    cin >> String;

    while(cin >> Rule) {
        char c = *Rule.begin();
        Rule.erase(Rule.begin());
        if(Rule.size() == 1) {
            One[Rule[0] - 'a'].insert(c);
        } else {
            Two[Rule[0] - 'A'][Rule[1] - 'A'].insert(c);
            Two[Rule[1] - 'A'][Rule[0] - 'A'].insert(c);
        }

        Rule.clear();
    }
}

void hasSolution() {
    cout << "1\n";
    exit(0);
}

void preProcessate() {
    for(int i = 0; i < (int)String.size(); i++) {
        Options[i][i] = One[String[i] - 'a'];
    }
}

void getSolution(int left, int right) {
    if((double)(clock() - startingTime) / CLOCKS_PER_SEC > 1.5) {
        hasSolution();
    }

    //cout << left << " " << right << '\n';

    if(!checked[left][right] && left != right) {
        checked[left][right] = true;
        for(int k = left; k < right; k++) {
            getSolution(left, k);
            getSolution(k + 1, right);

            for(char i : Options[left][k]) {
                for(char j : Options[k + 1][right]) {
                    for(char l : Two[i - 'A'][j - 'A']) {
                        Options[left][right].insert(l);
                    }
                }
            }

            if(left == 0 && right == (int)String.size() - 1 && Options[left][right].find('S') != Options[left][right].end()) {
                hasSolution();
            }
        }
    }
}

int main() {
    readInput();
    return 0;
    preProcessate();
    getSolution(0, (int)String.size() - 1);
    for(char c : Options[0][(int)String.size() - 1]) {
        if(c == 'S') {
            hasSolution();
        }
    }

    cout << "0\n";
    return 0;
}
