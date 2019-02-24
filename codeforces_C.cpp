/**
  *  Worg
  */
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;
//FILE *fin = freopen("main.in", "r", stdin);
//FILE *fout = freopen("main.out", "w", stdout);

const int kMaxInf = 1000000000;

string s;
int sum_cif;

vector<int > pos[3];

void Impossible() {
   cout << "-1"; exit(0);
}

void MakeLists() {
    for(int i = 0; i < (int)s.size(); i++) {
        pos[(s[i] - '0') % 3].push_back(i);
    }
}

int main() {
    cin >> s;
    for(int i = 0; i < (int)s.size(); i++) {
        sum_cif = (sum_cif + s[i] - '0') % 3;
    }
    MakeLists();

    if(sum_cif % 3 == 0) {
        cout << s;
    } else if(sum_cif % 3 == 1) {
        int cost = kMaxInf;
        //  Stergem un 1
        if((int)pos[1].size() != 0) {
            int where = pos[1].back();
            if(where != 0) {
                for(int i = 0; i < s.size(); i++) {
                    if(where != i) {
                        cout << s[i];
                    }
                }
                return 0;
            } else {
                cost = 1;
                for(int i = 1; i < s.size() && s[i] == '0'; i++) {
                    cost ++;
                }
            }
        }
        //  Stergem 2 doiari
        int cost_2 = kMaxInf;
        int a, b;
        if(pos[2].size() >= 2) {
            a = pos[2].back(); pos[2].pop_back();
            b = pos[2].back();

            cost_2 = 2;
            if(b == 0) {
                int i = 1;
                if(a == 1) {
                    i ++;
                }
                for(; i < s.size() && s[i] == '0'; i++) {
                    cost_2 ++;
                }

            }
        }

        if(cost == cost_2 && cost == kMaxInf) {
            Impossible();
        }
        if(cost < cost_2) {
            int i = 1;
            if(s.size() == 1) {
                Impossible();
            }
            while(i < s.size() && s[i] == '0') {
                i++;
            }

            if(i == s.size()) {
                cout << '0'; return 0;
            }
            for(; i < s.size(); i++) {
                cout << s[i];
            }
        } else {
            if(s.size() == 2) {
                Impossible();
            }

            int i = 0;
            if(b == 0) {
                i ++;
                if(a == 1) {
                    i ++;
                }
            }
            while(i < s.size() && s[i] == '0') {
                i++;
            }
            if(i == s.size()) {
                cout << '0';
            } else {

                int written = 0;
                for(; i < s.size(); i++) {
                    if(i != a && i != b) {
                        cout << s[i];
                        written ++;
                    }
                }
                if(written == 0) {
                    cout << '0';
                }
            }
        }
    } else {
        int cost = kMaxInf, cost_2 = kMaxInf;
        //  Eliminam un 2
        if(pos[2].size() >= 1) {
            int where = pos[2].back();
            if(where != 0) {
                for(int i = 0; i < s.size(); i++) {
                    if(i != where) {
                        cout << s[i];
                    }
                }
                return 0;
            } else {
                cost = 1;
                for(int i = 1; i < s.size() && s[i] == '0'; i++) {
                    cost ++;
                }
            }
        }
        //  Eliminam 2 de 1
        int a, b;
        if(pos[1].size() >= 2) {
            a = pos[1].back(); pos[1].pop_back();
            b = pos[1].back();

            int i = 0;
            cost_2 = 2;
            if(b == 0) {
                i++;
                if(a == 1) {
                    i++;
                }
                while(i < s.size() && s[i] == '0') {
                    i ++;
                    cost_2 ++;
                }
            }
        }

        if(cost == cost_2 && cost == kMaxInf) {
            Impossible();
        } else if(cost < cost_2) {  //  un doiar
            int i = 1;
            while(i < s.size() && s[i] == '0') {
                i++;
            }

            if(i == s.size()) {
                cout << '0';
            } else {
                for(; i < s.size(); i++) {
                    cout << s[i];
                }
            }
        } else {  //  2 de 1
            if(s.size() == 2) {
                Impossible();
            }
            int i = 0;
            if(b == 0) {
                i++;
                if(a == 1) {
                    i++;
                }
            }
            while(i < s.size() && s[i] == '0') {
                i++;
            }

            if(i == s.size()) {
                cout << '0';
            } else {
                int written = 0;
                while(i < s.size()) {
                    if(i != a && i != b) {
                        written ++;
                        cout << s[i];
                    }
                    i++;
                }
                if(!written) {
                    cout << '0';
                }
            }
        }
    }

    return 0;
}
