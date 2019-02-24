/**
  *  Worg
  */
#include <deque>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;
ifstream in("dir.in");
ofstream out("dir.out");

string S, aux, aux2;
deque < string > D, rez;
deque < string >::iterator it;
int pos, len, ans;
char c = 92;

void eval() {

    while( pos < len && S[pos] != ')' ) {

        if( 'A' <= S[pos] && S[pos] <= 'Z' ) {
            aux.clear();
            while( ('A' <= S[pos] && S[pos] <= 'Z') || ('0' <= S[pos] && S[pos] <= '9') ) {
                aux.push_back(S[pos]);
                ++pos;
            }
            D.push_back(aux);

            ++pos; eval();
        }

        else {
            aux.clear();
            while( ('a' <= S[pos] && S[pos] <= 'z') || ('0' <= S[pos] && S[pos] <= '9') ) {
                aux.push_back(S[pos]);
                ++pos;
            }

            aux2.clear();
            for(it = D.begin(); it != D.end(); ++it) {
                aux2 += *it;
                aux2 += c;
            }
            ++ans; aux2 += aux; rez.push_back( aux2 );
        }

        if( S[pos] == ',' )
            ++pos;
    }
    ++pos;

    if( !D.empty() )
        D.pop_back();
}

int main() {
    in >> S; len = S.size();
    eval();

    sort(rez.begin(), rez.end());

    out << ans << '\n';
    for(it = rez.begin(); it != rez.end(); ++it)
        out << *it << '\n';
}
