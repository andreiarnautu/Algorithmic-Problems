/**
  *  Worg
  */
#include <deque>
#include <cstdio>

using std::deque;
FILE *fin = freopen("main.in", "r", stdin);
FILE *fout = freopen("main.out", "w", stdout);

const int MAX_LENGTH = 1 + 32;

/*-------- Input data --------*/
char text[MAX_LENGTH];
/*-------- Algorithm data --------*/
deque<int > digits;
/*-------- --------*/

void ReadInput() {
    scanf("%s", text);
}

void GetDigits() {  //  We want to transform the string into numbers. For easier implementation, we can store them in a deque.
    char *s = text;

    while('0' <= *s && *s <= '9') {
        digits.push_back(*s - '0');
        s ++;
    }
}

int GetLeftNumber(const int last_value) {
    int value = 0;

    if(!digits.empty()) {
        do {
            value = value * 10 + digits.front();
            digits.pop_front();
        }while(!digits.empty() && value <= last_value);
    }

    return value;
}

int GetRightNumber(const int last_value) {
    int value = 0;

    if(!digits.empty()) {
        do {
            value = value * 10 + digits.back();
            digits.pop_back();
        }while(!digits.empty() && value <= last_value);
    }

    return value;
}

void GetNumbers() {
    int last_value = -1;
    int step = 0;
    bool ok = true;

    while(ok) {
        int value = 0;
        if(step == 0) {
            value = GetLeftNumber(last_value);
        } else {
            value = GetRightNumber(last_value);
        }

        if(value > last_value) {  //  We can output the current value
            printf("%d ", value);
            last_value = value;
            step ^= 1;
        } else {  //  We have to stop
            ok = false;
        }
    }

    printf("\n");

}

int main() {
    const int test_count = 5;
    for(int i = 1; i <= test_count; i++) {
        ReadInput();
        GetDigits();
        GetNumbers();
        digits.clear();
    }

    return 0;
}
