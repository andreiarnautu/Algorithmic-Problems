/**
  *  Worg
  */
#include <iostream>
#include <algorithm>

using namespace std;

const int NR_MAX_DIVIZORI = 200; /* nu am calculat exact, dar te gandesti ca un nr nu are mai multi de atat */

int divA[NR_MAX_DIVIZORI], divB[NR_MAX_DIVIZORI];
int posA, posB;

int main() {

    int a, b;
    cin >> a >> b;

    /* in divA vom avea divizorii lui a, in divB divizorii lui B */

    for(int i = 1; i * i <= a; ++i)
        if(a % i == 0) {
            posA++;
            divA[posA] = i;

            if(i * i < a) { /* verificam sa nu fie i radacina patrata a lui a */
                posA++;
                divA[posA] = a / i;
            }
        }

    for(int i = 1; i * i <= b; ++i) /* analog pentru b */
        if(b % i == 0) {
            posB++;
            divB[posB] = i;

            if(i * i < b) {
                posB++;
                divB[posB] = b / i;
            }
        }

    sort(divA + 1, divA + posA + 1);
    sort(divB + 1, divB + posB + 1);

    for(int i = 1; i <= posA; ++i) {

        bool gasit = false;
        for(int j = 1; j <= posB; ++j)
            if(divB[j] == divA[i]) {
                gasit = true;
                break;
            }

        if(gasit == true)
            cout << divA[i] << " ";
    }

    return 0;
}
