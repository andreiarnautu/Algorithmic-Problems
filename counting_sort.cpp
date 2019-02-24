/**
  *  Worg
  */

#include <fstream>

using namespace std;
ifstream fin("main.in");
ofstream fout("main.out");

const int MAX_VALUE = 1 + 100000;

int n;
int f[MAX_VALUE];

int main() {
    fin >> n;
    for(int i = 1; i <= n; i++) {
        int x; fin >> x;
        f[x] ++;
    }
    for(int i = 1; i < MAX_VALUE; i++) {
        while(f[i]) {
            fout << i << " ";
            f[i] --;
        }
    }
    return 0;
}
