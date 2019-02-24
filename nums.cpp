/**
  *  Worg
  */
#include <string>
#include <fstream>
#include <algorithm>

#define lsb(i) (i & (-i))

using namespace std;
ifstream fin("nums.in");
ofstream fout("nums.out");

const int MAX_N = 1 + 100000;

/*-------- Input data --------*/
int N;
int type;
int query_value[MAX_N];
string input_string[MAX_N];
/*-------- Algorithm data --------*/
string numbers[MAX_N], different_numbers[MAX_N];
int count_numbers, count_different_numbers;

bool checked[MAX_N];
int aib[MAX_N];
/*-------- --------*/

bool comp_numbers(string a, string b) {
    if(a.size() != b.size()) {
        return a.size() < b.size();
    } else {
        return a < b;
    }
}

void read_input() {
    fin >> N;
    for(int i = 1; i <= N; i++) {
        fin >> type;
        if(type == 0) {
            fin >> query_value[i];
        } else {
            fin >> input_string[i];
            numbers[++count_numbers] = input_string[i];
        }
    }
}

void get_different_numbers() {
    different_numbers[++count_different_numbers] = numbers[1];
    for(int i = 2; i <= count_numbers; i++) {
        if(numbers[i] != numbers[i - 1]) {
            different_numbers[++count_different_numbers] = numbers[i];
        }
    }
}

void aib_add(int pos, int value) {
    for(int i = pos; i <= count_different_numbers; i += lsb(i)) {
        aib[i] += value;
    }
}

void process_operations() {
    for(int i = 1; i <= N; i++) {
        if(query_value[i] == 0) {               /* Daca avem o operatie de adaugare a unui numar */
            int position = 0;
            for(int step = (1 << 16); step > 0; step >>= 1) {
                if(position + step <= count_different_numbers && comp_numbers(input_string[i], different_numbers[position + step]) == 0) {
                    position += step;
                }
            }
            if(!checked[position]) {
                aib_add(position, 1);
                checked[position] = true;
            }
        } else {                                /* Daca avem un query */
            int solution = 0;
            int before = 0;

            for(int step = (1 << 16); step > 0; step >>= 1) {
                if(solution + step < count_different_numbers && before + aib[solution + step] < query_value[i]) {
                    solution += step;
                    before += aib[solution];
                }
            }
            fout << different_numbers[solution + 1] << '\n';
        }
    }
}

int main() {
    read_input();
    sort(numbers + 1, numbers + count_numbers + 1, comp_numbers);
    get_different_numbers();
    process_operations();
    return 0;
}
