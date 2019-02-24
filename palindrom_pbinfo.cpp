/**
  *  Worg
  */
#include <fstream>
#include <cstring>

using namespace std;
ifstream fin("palindrom.in");
ofstream fout("palindrom.out");

int N;
char sir[20];
int lg;

int main() {
    fin >> N;
    for(int i = 1; i <= N; i++) {
        fin >> sir;
        lg = strlen(sir);

        bool ok = true;
        for(int i = 0, j = lg - 1; i <= j; i++, j--) {
            if(sir[i] != sir[j]) {
                ok = false; break;
            }
        }

        fout << ok << '\n';
    }

    return 0;
}
