/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;
FILE *fin = freopen("costuri.in", "r", stdin);
FILE *fout = freopen("costuri.out", "w", stdout);

const int MAX_N = 1 + 100000;
const int buffer_dim = 1 + 100000;

/*-------- Input Reader --------*/

class inputReader {
private:
        char buffer[buffer_dim];
        int pos;

        bool digit(char c) {
            return('0' <= c && c <= '9');
        }

public:
        void GetBuffer() {
            fread(buffer, 1, buffer_dim, stdin);
            pos = 0;
        }

        void operator >>(int &nr) {
            nr = 0;
            char c = '+';
            while(!digit(buffer[pos])) {
                c = buffer[pos];
                if(++pos == buffer_dim) {
                    GetBuffer();
                }
            }
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == buffer_dim) {
                    GetBuffer();
                }
            }
            if(c == '-') {
                nr = -nr;
            }
        }
} cin;
/*-------- Input data --------*/
int N, Q;
unordered_map<int, int > my_map;
vector<int > List[MAX_N];
int crt_index;
/*-------- --------*/

int DigitProduct(int k) {
    int answer = 1;

    do {
        answer *= (k % 10);
        k /= 10;
    }while(k != 0);

    return answer;
}

void ReadInput() {
    cin.GetBuffer();
    cin >> N;
    for(int i = 1; i <= N; i++) {
        int x; cin >> x;
        int digit_product = DigitProduct(x);

        if(my_map.find(digit_product) == my_map.end()) {
            crt_index ++;
            my_map[digit_product] = crt_index;
        }

        List[my_map[digit_product]].push_back(x);
    }
}

void AnswerQuery() {
    int index, value; cin >> index; cin >> value;
    if(my_map.find(value) == my_map.end()) {
        printf("-1\n");
    } else {
        value = my_map[value];
        if(index - 1 >= (int)List[value].size()) {
            printf("-1\n");
        } else {
            printf("%d\n", List[value][index - 1]);
        }
    }
}

int main() {
    ReadInput();
    for(cin >> Q; Q > 0; Q--) {
        AnswerQuery();
    }
    return 0;
}
