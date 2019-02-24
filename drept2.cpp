/**
  *  Worg
  */
#include <deque>
#include <cstdio>
#include <algorithm>

using std::deque;
FILE *fin = freopen("drept2.in", "r", stdin);
FILE *fout = freopen("drept2.out", "w", stdout);

const int buffer_dim = 1 + 100000;
const int MAX_N = 1 + 2000100;

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
int M, N, A, B;
int left[MAX_N], right[MAX_N];
/*-------- Algorithm data --------*/
deque< int > left_endings, right_endings;
/*-------- --------*/

void ReadInput() {
    cin.GetBuffer();
    cin >> M; cin >> N; cin >> A; cin >> B;

    int length;
    cin >> left[1]; cin >> length; right[1] = left[1] + length - 1;
    for(int i = 2; i <= N; i++) {
        cin >> left[i];
        int diff; cin >> diff;
        length += diff;
        right[i] = left[i] + length - 1;
    }
}

long long GetRectangles(long long x, long long y) {  //  Numarul de dreptunghiuri cu x linii si y coloane
    long long answer = 0;
    for(int i = 1; i <= N; i++) {
        //  Capetele din stanga
        while(!left_endings.empty() && left[left_endings.back()] <= left[i]) {
            left_endings.pop_back();
        }
        left_endings.push_back(i);
        if(left_endings.front() == i - x) {
            left_endings.pop_front();
        }

        //  Capetele din dreapta
        while(!right_endings.empty() && right[right_endings.back()] >= right[i]) {
            right_endings.pop_back();
        }
        right_endings.push_back(i);
        if(right_endings.front() == i - x) {
            right_endings.pop_front();
        }

        if(i >= x && right[right_endings.front()] - left[left_endings.front()] + 2 >= y) {
            answer += right[right_endings.front()] - left[left_endings.front()] - y + 2;
        }
    }

    left_endings.clear(); right_endings.clear();

    return answer;
}

long long GetSolution() {
    long long solution = GetRectangles(A, B);
    if(A != B) {
        solution += GetRectangles(B, A);
    }
    return solution;
}

int main() {
    ReadInput();
    printf("%lld\n", GetSolution());
    return 0;
}
